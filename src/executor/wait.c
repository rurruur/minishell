/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:21:20 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/25 10:17:51 by nakkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_toklst	*get_last_cmd(t_toklst *list)
{
	while (list && list->next)
		list = list->next;
	return (list);
}

static void	set_status(int status)
{
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_status = 128 + WTERMSIG(status);
	else
		g_status = 1;
}

void	ft_wait(t_toklst *list)
{
	pid_t		pid;
	t_toklst	*last_cmd;
	int			status;

	last_cmd = get_last_cmd(list);
	handle_sig(SIG_WAIT);
	pid = 0;
	while (pid != -1)
	{
		pid = wait(&status);
		if (pid != last_cmd->pid)
			continue ;
		set_status(status);
	}
	handle_sig(READLINE);
	while (list)
	{
		close(list->end[0]);
		list = list->next;
	}
}
