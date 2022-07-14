/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _signal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 17:02:57 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/15 00:22:08 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	h_sigint(int signum);
void	h_sigquit(int signum);

void	h_sigint(int signum)
{
	if (signum != SIGINT)
		return ;
	printf("ctrl + c print a new prompt on a newline\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	h_sigquit(int signum)
{
	if (signum != SIGQUIT)
		return ;
	printf("ctrl + \\ do nothing\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}
