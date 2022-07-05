/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:59:23 by jrim              #+#    #+#             */
/*   Updated: 2022/07/05 14:22:09 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char		*line;
	t_toklst	*toklst;

	signal(SIGINT, h_sigint);      // ctrl + c
	signal(SIGQUIT, h_sigquit);    // ctrl + '\'
	while (1)
	{
		line = readline(PRMPT);
		if (line)
		{
			add_history(line);
			toklst = (t_toklst *)malloc(sizeof(t_toklst));
			if (!toklst)
				err_msg("allocation");
			// parser_main(line, toklst);
			// executor(toklst);
			printf("%s%s\n", PRMPT, line);
			free(line);
			line = NULL;
		}
		else // ctrl + d
		{
			printf("\b\bctrl + d exit the shell\n");
			break;
		}
	}
	return (0);
}
