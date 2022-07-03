/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:59:23 by jrim              #+#    #+#             */
/*   Updated: 2022/07/04 00:09:17 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;
	char	**cmd_token;

	signal(SIGINT, h_sigint);      // ctrl + c
	signal(SIGQUIT, h_sigquit);    // ctrl + '\'
	while (1)
	{
		line = readline(PRMPT);
		if (line)
		{
			add_history(line);
			// error check
			if (!check_quote(line))
				err_msg("quote");
            // else
            //     printf("%s%s\n", PRMPT, line);
			cmd_token = ft_split(line, ' ');
			if (cmd_token[0] && !check_pipe(cmd_token))
				err_msg("pipe");
			free(line);
			free_all(cmd_token);
			line = NULL;
			cmd_token = NULL;
		}
		else // ctrl + d
		{
			printf("\b\bctrl + d exit the shell\n");
			break;
		}
	}
	return (0);
}
