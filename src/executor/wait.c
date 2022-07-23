/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:21:20 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/23 16:18:53 by nakkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_toklst	*get_last_cmd(t_toklst *list)
{
	while (list && list->next)
	{
		list = list->next;
	}
	return (list);
}

void	ft_wait(t_toklst *list)
{
	pid_t		pid;
	int			cmd_count;
	t_toklst	*last_cmd;

	// display_toklst(list);
	cmd_count = get_pipe_count(list);
	g_status = 0;
	last_cmd = get_last_cmd(list);
	handle_sig(SIG_WAIT);
	pid = 0;
	while (pid != -1)
	{
		pid = wait(&g_status);
		if (pid != last_cmd->pid)
			continue ;
		if (WIFEXITED(g_status))
		{
			if (WEXITSTATUS(g_status))
				g_status = WEXITSTATUS(g_status);
		}
		else if (WIFSIGNALED(g_status))
			g_status = 128 + WTERMSIG(g_status);
		else
			g_status = 1;
	}
	handle_sig(READLINE);
	while (list)
	{
		close(list->end[0]);
		list = list->next;
	}
}
