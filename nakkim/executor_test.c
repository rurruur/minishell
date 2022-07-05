# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"

typedef struct s_token
{
	int		rdr_in;		//	< 유무
	char	**infile;	//	infile name
	char	*cmd;		//	cmd일 것으로 예상되는 str
	char	**param;	//	cmd 뒤에 오는 str들의 배열
	int		rdr_out;	//	> 유무
	char	**outfile;	//	outfile name
	int		rdr_app;	//	>> 유무
	char	**appfile;	//	append 되어야할 file name
} 			t_token;

typedef struct s_toklst
{
	t_token			node;	//	각 노드는 |를 기준으로 나누어져있습니다.
	struct s_toklst	*next;
} 	t_toklst;

char	*get_cmd_path(char *cmd, char **path);
void	executor(t_toklst *list, char **env);

int	main(int argc, char **argv, char **env)
{
	t_toklst	*head;
	t_toklst	first;
	t_toklst	second;
	t_token		first_token;
	t_token		second_token;
	char		*param[] = { "hi" };
	char		*infiles[] = { "infile", NULL };
	char		*outfiles[] = { "outfile", NULL };

	first_token.rdr_in = 1;
	first_token.infile = infiles;
	first_token.cmd = "grep";
	first_token.param = param;
	first_token.rdr_out = 1;
	first_token.outfile = outfiles;
	first_token.rdr_app = 0;

	// first_token.rdr_in = 1;
	// first_token.infile = infiles;
	// first_token.cmd = "grep";
	// first_token.param = param;
	// first_token.rdr_out = 0;
	// first_token.outfile = outfiles;
	// first_token.rdr_app = 0;

	first.node = first_token;
	first.next = NULL;
	head = &first;

	executor(head, env);

	return (0);
}

int	is_file_exist(char **infile, int create)
{
	int	i;
	int	infile_fd;

	i = 0;
	while (infile[i])
	{
		if (create)
			infile_fd = open(infile[i], O_WRONLY | O_CREAT);
		else
			infile_fd = open(infile[i], O_RDONLY);
		if (infile_fd < 0)
			break ;
		close(infile_fd);
		i++;
	}
	return (i);
}

void	executor(t_toklst *list, char **env)
{
	int			end[2];
	int			exit_status;
	pid_t		child;
	int			status;


	// 환경변수 PATH
	char	*env_path = ft_substr(env[4], 5, ft_strlen(env[4]));
	char	**path = ft_split(env_path, ':');

	while (list != NULL)
	{
		child = fork();
		if (child == 0)
		{
			// STDIN 설정
			if (list->node.rdr_in) {
				// 인파일들 존재 확인
				int	i;
				int	infile_fd;

				i = is_file_exist(list->node.infile, 0);
				if (list->node.infile[i])
					perror(list->node.infile[i]);
					//해당 노드는 실행 x
				infile_fd = open(list->node.infile[i - 1], O_RDONLY);
				// STDIN을 마지막 파일로 설정
				if (dup2(infile_fd, STDIN_FILENO) < 0)
					perror("dup2 - in");
			}
			// STDOUT 설정
			if (list->node.rdr_out) {
				// 아웃파일들 존재 확인
				int	i;
				int	outfile_fd;

				i = is_file_exist(list->node.outfile, 1);
				outfile_fd = open(list->node.outfile[i - 1], O_WRONLY);
				// STDOUT을 마지막 파일로 설정
				if (dup2(outfile_fd, STDOUT_FILENO) < 0)
					perror("dup2 - out");
			}
			if (list->node.cmd)
			{
				// 명령어 경로 찾기
				char	*cmd = get_cmd_path(list->node.cmd, path);
				if (!cmd)
					perror("Cannot find cmd path");

				// 명령 실행
				char *cmd_line[] = { list->node.cmd, list->node.param[0], NULL };
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