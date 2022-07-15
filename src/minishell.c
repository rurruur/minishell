/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:59:23 by jrim              #+#    #+#             */
/*   Updated: 2022/07/16 02:33:09 by jrim             ###   ########.fr       */
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
			toklst = tokenizer(line, NULL);
			if (toklst)
			{
				display_toklst(toklst);
				executor(toklst, env);
			}
			free_toklst(toklst);
			// system("leaks minishell > leaks_result; cat leaks_result | grep leaked && rm -rf leaks_result");
		}
		else
			break;
		free(line);
	}
	return (0);
}
