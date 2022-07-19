/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:21:20 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/19 21:35:16 by nakkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_wait(void)
{
	g_status = 0;
	while (wait(&g_status) != -1);
	if (WIFEXITED(g_status))
	{
		g_status = WEXITSTATUS(g_status);
		dprintf(g_fd, "exit: %d\n", g_status);
	}
	else if (WIFSIGNALED(g_status))
	{
		g_status = 128 + WTERMSIG(g_status);
		dprintf(g_fd, "signal: %d\n", g_status);
	}
	else
		g_status = 1;
}
