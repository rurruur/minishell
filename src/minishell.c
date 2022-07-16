/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:59:23 by jrim              #+#    #+#             */
/*   Updated: 2022/07/16 16:34:06 by nakkim           ###   ########.fr       */
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
	g_fd = open("global", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	while (argc)
	{
		line = readline(PRMPT);
		dprintf(g_fd, "\n---readline(%s)---\n", line);
		if (line)
		{
			add_history(line);
			toklst = tokenizer(line, NULL);
			if (toklst)
			{
				// display_toklst(toklst);
				executor(toklst, env);
			}
			// free_toklst(toklst);
			// // system("leaks minishell > leaks_result; cat leaks_result | grep leaked && rm -rf leaks_result");
			free(line);
		}
		else
			break;
	}
	close(g_fd);
	return (0);
}
