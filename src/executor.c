/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 23:03:49 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/14 22:59:34 by nakkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// in, out 나눠 말아...
int	set_file_redirection(t_token *files, enum e_rdr mode)
{
	int	fd;
	int	result;

	while (files)
	{
		if (mode == IN)
			fd = open(files->str, O_RDONLY);
		else
			fd = open(files->str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd < 0)
			return (0);
		if (files->next == NULL)
			break ;
		close(fd);
		files = files->next;
	}
	if (mode == IN)
		result = dup2(fd, STDIN_FILENO);
	else
		result = dup2(fd, STDOUT_FILENO);
	if (result < 0)
		return (-1);
	close(fd);
	return (1);
}

void	set_redirection(t_toklst *list, int *end)
{
	int	result;

	if (list->infile)
	{
		// STDIN 설정
		result = set_file_redirection(list->infile, IN);
		if (result == 0)
			perror("redirection error");	// infile 하나라도 없는 경우: 해당 노드는 실행 x
		else if (result == -1)
			perror("dup2");		// 어캐 해야? 걍 종료?
	}
	if (list->outfile)
	{
		// STDOUT 설정
		result = set_file_redirection(list->outfile, OUT);
		if (result == 0)
			perror("open error");	// outfile open error: 어캐 처리??
		else if (result == -1)
			perror("dup2");
	}
	else if (list->next != NULL)	// out redirection 없고, 마지막 명령어가 아닐 경우 파이프로 표준출력
	{
		close(end[0]);
		if (dup2(end[1], STDOUT_FILENO) < 0)
			perror("dup2");
	}
	// 	// STDIN 설정
	// if (list->infile && !set_file_redirection(list->infile, IN))
	// 	perror("redirection error");	// infile 하나라도 없는 경우: 해당 노드는 실행 x
	// // STDOUT 설정
	// if (list->outfile && !set_file_redirection(list->outfile, OUT))
	// 	perror("redirection error");	// outfile open error: 어캐 처리??
	// else if (list->next != NULL)	// out redirection 없고, 마지막 명령어가 아닐 경우 파이프로 표준출력
	// {
	// 	close(end[0]);
	// 	if (dup2(end[1], STDOUT_FILENO) < 0)
	// 		perror("dup2");
	// }
}

int	is_builtin(char *cmd)
{
	int	cmd_len;

	cmd_len = ft_strlen(cmd);
	// 옵션 같은 경우는 어떻게..? 옵션 있으면 구현 해야하는 거인지 확인 하고 맞으면 빌트인?
	// 예를 들면 echo -n 은 빌트인으로 처리하는데
	// echo -e는 execve로 실행햐야 하는 거 아냐
	if (ft_strncmp("exit", cmd, cmd_len) || ft_strncmp("echo", cmd, cmd_len)
		|| ft_strncmp("cd", cmd, cmd_len) || ft_strncmp("pwd", cmd, cmd_len)
		|| ft_strncmp("export", cmd, cmd_len)
		|| ft_strncmp("unset", cmd, cmd_len) || ft_strncmp("env", cmd, cmd_len))
		return (1);
	return (0);
}

void	child_process(t_toklst *list, int *end, char **env)
{
	char	*cmd;
	char	**cmd_line;

	set_redirection(list, end);
	if (list->cmd)
	{
		if (is_builtin(list->cmd->str))
			;
		cmd = get_valid_cmd_path(list->cmd->str);
		if (!cmd) {
			// cmd 못찾은 경우
			exit(1);
		} else {
			// cmd free 필요
			cmd_line = list_to_arr(list->cmd);	// 각각 free 필요?
			if (!execve(cmd, cmd_line, env))
			{
				perror("execve");
				free(cmd);
				destroy_split(cmd_line);
			}
		}
	}
}

void	parent_process(pid_t child, int *end)
{
	int		status;

	close(end[1]);	// 에러??
	if (dup2(end[0], STDIN_FILENO) < 0)
		perror("dup2");
	waitpid(child, &status, 0);
}

void	executor(t_toklst *list, char **env)
{
	int		end[2];
	pid_t	child;

	while (list != NULL)
	{
		if (pipe(end) == -1)
		{
			perror("pipe");
			return ;	// 리턴할지 아니면 다음 명령어로 넘어갈지 결정
		}
		child = fork();
		if (child == -1)
		{
			perror("fork");
			return ;
		}
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

void	destroy_split(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

char	*get_valid_cmd_path(char *cmd)
{
	struct stat	stat_result;
	char		*cmd_path;
	char		**path;
	int			i;
	
	path = ft_split(getenv("PATH"), ':');	// free?
	i = -1;
	while (path[++i])
	{
		cmd_path = double_strjoin(path[i], "/", cmd);
		if (stat(cmd_path, &stat_result) != -1)
			break ;
		free(cmd_path);
	}
	destroy_split(path);
	if (!path[i]) {	// 여기 에러 처리 좀 더 고민
		return (0);
	}
	return (cmd_path);
}