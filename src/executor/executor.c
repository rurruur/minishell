/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 23:03:49 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/15 21:15:00 by nakkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			dprintf(g_fd, "cmd execute(pid: %d)\n", getpid());
			if (!execve(cmd, cmd_line, env))
			{
				perror("execve");
				free(cmd);
				destroy_split(cmd_line);
			}
		}
	}
	exit(1);
}

void	parent_process(pid_t child, int *end)
{
	int		status;

	close(end[1]);	// 에러??
	if (dup2(end[0], STDIN_FILENO) < 0)
		perror("dup2");
	waitpid(child, &status, 0);
}

void	print_list(t_toklst *list)
{
	t_token	*tmp;
	
		dprintf(g_fd, "========node(%p)=======\n", list);
		dprintf(g_fd, "cmd: ");
		tmp = list->cmd;
		while (tmp)
		{
			dprintf(g_fd, "%s ", tmp->str);
			tmp = tmp->next;
		}
		dprintf(g_fd, "next: %p\n", list->next);
		
		dprintf(g_fd, "===================================\n");
}

void	executor(t_toklst *list, char **env)
{
	int		end[2];
	pid_t	child;

	while (list != NULL)
	{
		print_list(list);
		dprintf(g_fd, "\n= executor(%d) =\n", getpid());
		if (pipe(end) == -1)
		{
			perror("pipe");
			return ;	// 리턴할지 아니면 다음 명령어로 넘어갈지 결정
		}
		child = fork();
		dprintf(g_fd, "fork: %d\n", getpid());
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
