# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"

FILE	*fp;

// typedef struct s_token
// {
// 	int		rdr_in;		//	< 유무
// 	char	**infile;	//	infile name
// 	char	*cmd;		//	cmd일 것으로 예상되는 str
// 	char	**param;	//	cmd 뒤에 오는 str들의 배열
// 	int		rdr_out;	//	> 유무
// 	char	**outfile;	//	outfile name
// 	int		rdr_app;	//	>> 유무
// 	char	**appfile;	//	append 되어야할 file name
// } 			t_token;

// typedef struct s_toklst
// {
// 	t_token			node;	//	각 노드는 |를 기준으로 나누어져있습니다.
// 	struct s_toklst	*next;
// } 	t_toklst;

typedef struct s_token
{
	char			*str;
	struct s_token	*next;
} 					t_token;

typedef struct s_toklst
{
	t_token			*cmd;		//	cmd와 뒤에 오는 str들
	t_token			*infile;	//	< : infile name
	t_token			*outfile;	//	> : outfile name
	t_token			*here_doc;	//	<< : here_doc에 들어가는 str들
	t_token			*append;	//	>> : append 되어야할 file name
	struct s_toklst	*next;
} 					t_toklst;

char	*get_cmd_path(char *cmd, char **path);
void	executor(t_toklst *list, char **env);
char	**list_to_arr(t_token *list);

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

	first->cmd->str = "cat";
	first->cmd->next = (t_token *)malloc(sizeof(t_token));
	first->cmd->next->str = "infile";
	first->cmd->next->next = NULL;
	first->infile = NULL;
	first->outfile = NULL;
	first->here_doc = NULL;
	first->append = NULL;
	first->next = second;

	second->cmd->str = "cat";
	second->cmd->next = NULL;
	second->infile = NULL;
	second->outfile->str = "outfile";
	second->outfile->next = NULL;
	second->here_doc = NULL;
	second->append = NULL;
	second->next = NULL;

	fp = fopen("/Users/kimnakyeong/minishell/nakkim/fprintf", "w");

	executor(first, env);

	fclose(fp);
	return (0);
}

void	executor(t_toklst *list, char **env)
{
	int			end[2];
	pid_t		child;
	int			status;
	int			flag;

	// 환경변수 PATH
	char	*env_path = ft_substr(env[4], 5, ft_strlen(env[4]));
	char	**path = ft_split(env_path, ':');

	pipe(end);
	flag = 0;

	while (list != NULL)
	{
		child = fork();
		if (child == 0)
		{
			// STDIN 설정
			if (list->infile) {
				// 인파일들 존재 확인
				int		fd;
				t_token	*curr_file;

				curr_file = list->infile;
				while (curr_file)
				{
					fd = open(curr_file->str, O_RDONLY);
					if (fd < 0)	//infile 하나라도 없는 경우: 해당 노드는 실행 x
						perror("file open error");
					close(fd);
					if (curr_file->next == NULL)
						break ;
					curr_file = curr_file->next;
				}
				// STDIN을 마지막 파일로 설정
				fd = open(curr_file->str, O_RDONLY);
				if (dup2(fd, STDIN_FILENO) < 0)
					perror("dup2 - infile");
				fprintf(fp, "dup2 - in(file)\n");
				close(fd);
			}
			else if (flag)
			{
				if (dup2(end[0], STDIN_FILENO) < 0)
					perror("dup2 - in");
				flag = 0;
				fprintf(fp, "dup2 - in(flag 0)\n");
				close(end[0]);
			}
			else
			{
				if (dup2(end[1], STDIN_FILENO) < 0)
					perror("dup2 - in");
				flag = 1;
				fprintf(fp, "dup2 - in(flag 0)\n");
				close(end[1]);
			}
			// STDOUT 설정
			if (list->outfile) {
				// 인파일들 존재 확인
				int		fd;
				t_token	*curr_file;

				curr_file = list->outfile;
				while (curr_file)
				{
					fd = open(curr_file->str, O_WRONLY | O_CREAT);	//outfile 하나라도 없는 경우: 생성
					if (fd < 0)
						perror("file open error");
					close(fd);
					if (curr_file->next == NULL)
						break ;
					curr_file = curr_file->next;
				}
				// STDOUT을 마지막 파일로 설정
				fd = open(curr_file->str, O_WRONLY);
				if (dup2(fd, STDOUT_FILENO) < 0)
					perror("dup2 - outfile");
				fprintf(fp, "dup2 - out(file)\n");
			}
			else if (flag)
			{
				if (dup2(end[0], STDOUT_FILENO) < 0)
					perror("dup2 - out");
				flag = 0;
				fprintf(fp, "dup2 - out(flag 1)\n");
			}
			else
			{
				if (dup2(end[1], STDOUT_FILENO) < 0)
					perror("dup2 - out");
				flag = 1;
				fprintf(fp, "dup2 - out(flag 0)\n");
			}
			if (list->cmd)
			{
				// 명령어 경로 찾기
				char	*cmd = get_cmd_path(list->cmd->str, path);
				if (!cmd)
					perror("command not found");
				// 명령 실행
				fprintf(fp, "%s 실행\n", list->cmd->str);
				char **cmd_line = list_to_arr(list->cmd);
				execve(cmd, cmd_line, env);
				perror("execve");
			}
		}
		else
		{
			close(end[1]);
			close(end[0]);
			waitpid(child, &status, 0);
		}
		list = list->next;
	}
}

char	**list_to_arr(t_token *list)
{
	char	**arr;
	int		size;
	t_token	*curr;

	size = 0;
	curr = list;
	while (curr)
	{
		curr = curr->next;
		size++;
	}
	arr = (char **)malloc(sizeof(char *) * (size + 1));
	arr[size] = NULL;
	size = 0;
	while (list)
	{
		arr[size++] = ft_strdup(list->str);
		list = list->next;
	}
	return (arr);
}

char	*get_cmd_path(char *cmd, char **path)
{
	int		i;
	char 	*cmd_path;

	for (i = 0; path[i]; i++) {
		char *str = ft_strjoin(path[i], "/");
		cmd_path = ft_strjoin(str, cmd);
		free(str);
		if (!access(cmd_path, X_OK))
			break ;
		free(cmd_path);
	}
	if (!path[i])
		return (0);
	return (cmd_path);
}