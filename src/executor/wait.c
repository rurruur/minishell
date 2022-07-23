/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:21:20 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/23 15:32:05 by nakkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_wait(t_toklst *list)
{
	g_status = 0;
	handle_sig(SIG_WAIT);
	while (wait(&g_status) != -1)
		;
	if (WIFEXITED(g_status))
	{
		if (WEXITSTATUS(g_status))
			g_status = WEXITSTATUS(g_status);
	}
	else if (WIFSIGNALED(g_status))
		g_status = 128 + WTERMSIG(g_status);
	else
		g_status = 1;
	handle_sig(READLINE);
	while (list)
	{
		close(list->end[0]);
		list = list->next;
	}
}
