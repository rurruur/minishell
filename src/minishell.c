/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:59:23 by jrim              #+#    #+#             */
/*   Updated: 2022/07/11 23:57:59 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_toklst	*toklst;

	(void)argc;
	(void)argv;

	signal(SIGINT, h_sigint);      // ctrl + c
	signal(SIGQUIT, h_sigquit);    // ctrl + '\'
	while (1)
	{
		line = readline(PRMPT);
		if (line)
		{
			add_history(line);
			if (!check_quote(line))	// 짝 안맞는 따옴표는 미리 거르기
				err_msg("quote");	// escape 처리는?
			else
			{
				toklst = init_toklst();
				if (tokenizer(line, toklst))
				{
					// display_toklst(toklst);
					executor(toklst, env);
				}
			}
			// free_toklst(&toklst);
		}
		else // ctrl + d
		{
			printf("\b\bctrl + d exit the shell\n");
			break;
		}
		free(line);
	}
	return (0);
}
