/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:59:23 by jrim              #+#    #+#             */
/*   Updated: 2022/07/15 14:12:08 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_toklst	*toklst;

	(void)argv;
	handle_sig();
	// env copy해오기?
	while (argc)
	{
		line = readline(PRMPT);
		if (line)
		{
			add_history(line);
			toklst = init_toklst();
			if (tokenizer(line, toklst))
			{
				display_toklst(toklst);
				if (!env)
					executor(toklst, env);
			}
			free_toklst(&toklst);
			// system("leaks minishell");
		}
		else // ctrl + d
			break;
		free(line);
	}
	return (0);
}
