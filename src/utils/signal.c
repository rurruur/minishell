/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 17:02:57 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/19 22:50:11 by nakkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	h_sigint(int signum);
void	h_sigquit(int signum);
void	handle_sig(enum e_sig_mode mode);

void	handle_sig(enum e_sig_mode mode)
{
	if (mode == READLINE)
	{
		signal(SIGINT, h_sigint);
		signal(SIGQUIT, h_sigquit);
	}
	else if (mode == HEREDOC)
	{
		signal(SIGINT, h_sigint);
		signal(SIGQUIT, h_sigquit);
	}
}

void	h_sigint(int signum)
{
	if (signum != SIGINT)
		return ;
	rl_on_new_line();
	rl_redisplay();
	printf("  \b\b\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	h_sigquit(int signum)
{
	if (signum != SIGQUIT)
		return ;
	rl_on_new_line();
	rl_redisplay();
	printf("  \b\b");
}
