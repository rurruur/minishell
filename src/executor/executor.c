/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 23:03:49 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/18 13:24:02 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_process(t_toklst *list, t_env *envlst)
{
	char	*cmd;
	char	**cmd_arr;
	char	**env;

	set_redirection(list);
	if (list->cmd)
	{
		if (builtin_main(list->cmd->str, list->cmd, envlst))
			exit(1);
			// free는해야돼..
		cmd = get_valid_cmd_path(list->cmd->str, envlst);
		if (!cmd) {
			// cmd 못찾은 경우
			perror("command");
			exit(1);
		} else {
			// cmd free 필요
			cmd_arr = list_to_arr(list->cmd);	// 각각 free 필요?
			dprintf(g_fd, "cmd execute(pid: %d)\n", getpid());
			env = get_env(envlst);
			close(list->end[0]);
			close(list->end[1]);
			if (!execve(cmd, cmd_arr, env))
			{
				perror("execve");
				free(cmd);
				// env free
				destroy_split(cmd_arr);
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

void	executor(t_toklst *list, t_env *envlst)
{
	t_toklst	*tmp;
	pid_t	child;

	dprintf(g_fd, "\n= executor(%d) =\n", getpid());
	tmp = list;
	while (tmp)
	{
		if (pipe(tmp->end) == -1)	// 다음 노드가 있을 경우 파이프 생성
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
			child_process(tmp, envlst);
		// close(tmp->end[0]);
		close(tmp->end[1]);
		tmp = tmp->next;
	}
	while (wait(&g_status) != -1);
	tmp = list;
	while (tmp)
	{
		close(tmp->end[0]);
		tmp = tmp->next;
	}
	dprintf(g_fd, "exit: %d\n", WEXITSTATUS(g_status));
}
