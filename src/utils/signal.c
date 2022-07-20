/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 17:02:57 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/20 13:41:04 by nakkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	h_sigint(int signum);
void	h_sigquit(int signum);
void	handle_sig(enum e_sig_mode mode);

static void	ft_exit()
{
	rl_on_new_line();
	rl_redisplay();
	printf("  \b\b\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	exit(1);
}

void	handle_sig(enum e_sig_mode mode)
{
	if (mode == READLINE)
	{
		signal(SIGINT, h_sigint);
		signal(SIGQUIT, h_sigquit);
	}
	else if (mode == HEREDOC)
	{
		signal(SIGINT, ft_exit);
		signal(SIGQUIT, h_sigquit);
	}
	else if (mode == WAIT_HEREDOC)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
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
