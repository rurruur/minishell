/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 17:02:57 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/17 13:52:28 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	h_sigint(int signum);
void	h_sigquit(int signum);
void	handle_sig(void);

void	handle_sig(void)
{
	signal(SIGINT, h_sigint);
	signal(SIGQUIT, h_sigquit);
}

void	h_sigint(int signum)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (signum != SIGINT)
		return ;
	if (pid == -1)
	{
		rl_on_new_line();
		rl_redisplay();
		printf("  \b\b\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	else
		printf("\n");
}

void	h_sigquit(int signum)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (signum != SIGQUIT)
		return ;
	if (pid == -1)
	{
		rl_on_new_line();
		rl_redisplay();
		printf("  \b\b");
	}
	else
		printf("\n");
}
