/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 23:03:49 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/11 23:06:01 by nakkim           ###   ########.fr       */
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
		if (fd < 0)	//infile 하나라도 없는 경우: 해당 노드는 실행 x
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
		return (0);
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

	set_redirection(list, end);
	if (list->cmd)
	{
		cmd = get_valid_cmd_path(list->cmd->str);	// free? + cmd == NULL 처리
		cmd_line = list_to_arr(list->cmd);	// 각각 free 필요?
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
	char		*cmd_path;
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