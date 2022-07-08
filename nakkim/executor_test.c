# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <sys/stat.h>

# define IN 0
# define OUT 1

typedef struct s_token
{
	char			*str;
	struct s_token	*next;
} 					t_token;

int	g_fd;

typedef struct s_toklst
{
	t_token			*cmd;		//	cmd와 뒤에 오는 str들
	t_token			*infile;	//	< : infile name
	t_token			*outfile;	//	> : outfile name
	t_token			*here_doc;	//	<< : here_doc에 들어가는 str들
	t_token			*append;	//	>> : append 되어야할 file name
	struct s_toklst	*next;
} 					t_toklst;

int		set_file_redirection(t_token *files, int mode);
void	set_redirection(t_toklst *list, int *end);
void	child_process(t_toklst *list, int *end, char **env);
void	parent_process(pid_t child, int *end);
void	executor(t_toklst *list, char **env);
int		get_cmd_count(t_token *cmds);
char	**list_to_arr(t_token *cmds);
char	*double_strjoin(char *start, char *middle, char *end);
char	*get_valid_cmd_path(char *cmd);

t_toklst	*init_node(void)
{
	t_toklst	*new;

	new = (t_toklst *)malloc(sizeof(t_toklst));
	new->cmd = (t_token *)malloc(sizeof(t_token));
	new->infile = (t_token *)malloc(sizeof(t_token));
	new->outfile = (t_token *)malloc(sizeof(t_token));
	new->here_doc = (t_token *)malloc(sizeof(t_token));
	new->append = (t_token *)malloc(sizeof(t_token));
	new->next = NULL;
	return (new);
}

int	main(int argc, char **argv, char **env)
{
	t_toklst	*first = init_node();
	t_toklst	*second = init_node();
	t_toklst	*third = init_node();

	first->cmd->str = "cat";
	first->cmd->next = (t_token *)malloc(sizeof(t_token));
	first->cmd->next->str = "infile";
	first->cmd->next->next = NULL;
	first->infile = NULL;
	first->outfile = NULL;
	first->here_doc = NULL;
	first->append = NULL;
	first->next = second;

	second->cmd->str = "grep";
	second->cmd->next = (t_token *)malloc(sizeof(t_token));
	second->cmd->next->str = "hi";
	second->cmd->next->next = NULL;
	second->infile = NULL;
	second->outfile = NULL;
	// second->outfile->str = "outfile";
	// second->outfile->next = NULL;  
	second->here_doc = NULL;
	second->append = NULL;
	second->next = third;

	third->cmd->str = "grep";
	third->cmd->next = (t_token *)malloc(sizeof(t_token));
	third->cmd->next->str = "asdf";
	third->cmd->next->next = NULL;
	third->infile = NULL;
	// third->outfile = NULL;
	third->outfile->str = "outfile";
	third->outfile->next = NULL;
	// third->outfile->next = (t_token *)malloc(sizeof(t_token));
	// third->outfile->next->str = "outfile2";
	// third->outfile->next->next = NULL;
	third->here_doc = NULL;
	third->append = NULL;
	third->next = NULL;

	g_fd = open("test", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dprintf(g_fd, "file open\n");

	executor(first, env);

	close(g_fd);
	return (0);
}

// in, out 나눠 말아...
int	set_file_redirection(t_token *files, int mode)
{
	int	fd;
	int	result;

	while (files)
	{
		if (mode == IN)
			fd = open(files->str, O_RDONLY);
		else
			fd = open(files->str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd < 0)	//infile 하나라도 없는 경우: 해당 노드는 실행 x
			return (0);
		if (files->next == NULL)
			break ;
		close(fd);
		files = files->next;
	}
	if (mode == IN)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	if (result < 0)
		return (0);
	dprintf(g_fd, "%s redirection set\n", mode == IN ? "IN" : "OUT");
	close(fd);
	return (1);
}

void	set_redirection(t_toklst *list, int *end)
{

	// STDIN 설정
	if (list->infile && !set_file_redirection(list->infile, IN))
		perror("redirection error");
	// STDOUT 설정
	if (list->outfile && !set_file_redirection(list->outfile, OUT))
		perror("redirection error");
	else if (list->next != NULL)	// out redirection 없고, 마지막 명령어가 아닐 경우 파이프로 표준출력
	{
		close(end[0]);
		if (dup2(end[1], STDOUT_FILENO) < 0)
			perror("dup2");
	}
}

void	child_process(t_toklst *list, int *end, char **env)
{
	char	*cmd;
	char	**cmd_line;

	dprintf(g_fd, "\nchild process\n");
	set_redirection(list, end);
	if (list->cmd)
	{
		cmd = get_valid_cmd_path(list->cmd->str);	// free? + cmd == NULL 처리
		cmd_line = list_to_arr(list->cmd);	// 각각 free 필요?
		dprintf(g_fd, "실행: %s, %s, %s\n", cmd, cmd_line[0], cmd_line[1]);
		if (!execve(cmd, cmd_line, env))
			perror("execve");
	}
}

void	parent_process(pid_t child, int *end)
{
	int		status;

	close(end[1]);
	dup2(end[0], STDIN_FILENO);
	waitpid(child, &status, 0);
}

void	executor(t_toklst *list, char **env)
{
	int		end[2];
	pid_t	child;
	
	while (list != NULL)
	{
		pipe(end);
		child = fork();
		if (child == 0)
			child_process(list, end, env);
		else
			parent_process(child, end);
		list = list->next;
	}
}

int	get_cmd_count(t_token *cmds)
{
	int	size;

	size = 0;
	while (cmds)
	{
		cmds = cmds->next;
		size++;
	}
	return (size);
}

char	**list_to_arr(t_token *cmds)
{
	char	**arr;
	int		count;

	count = get_cmd_count(cmds);
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	arr[count] = NULL;
	count = 0;
	while (cmds)
	{
		arr[count++] = ft_strdup(cmds->str);
		cmds = cmds->next;
	}
	return (arr);
}

char	*double_strjoin(char *start, char *middle, char *end)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(start, middle);
	result = ft_strjoin(tmp, end);
	free(tmp);
	return (result);
}

char	*get_valid_cmd_path(char *cmd)
{
	struct stat	stat_result;
	char 		*cmd_path;
	char		**path;
	int			i;
	
	// PATH=/opt/homebrew/bin:/opt/homebrew/sbin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin
	path = ft_split(getenv("PATH"), ':');	// free?
	i = -1;
	while (path[++i])
	{
		cmd_path = double_strjoin(path[i], "/", cmd);
		if (stat(cmd_path, &stat_result) != -1)
			break ;
		free(cmd_path);
	}
	if (!path[i]) {	// 여기 에러 처리 좀 더 고민
		free(cmd_path);
		return (0);
	}
	return (cmd_path);
}