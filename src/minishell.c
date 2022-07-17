/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:59:23 by jrim              #+#    #+#             */
/*   Updated: 2022/07/17 19:46:12 by nakkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_env		*envlst;
	t_toklst	*toklst;

	(void)argv;
	handle_sig();
	g_status = 0;
	envlst = copy_env(env, NULL);
	g_fd = open("global", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	while (argc)
	{
		line = readline(PRMPT);
		dprintf(g_fd, "\n---readline(%s)---\n", line);
		if (line)
		{
			add_history(line);
			toklst = tokenizer(line, NULL, envlst);
			if (toklst)
			{
				// display_toklst(toklst);
				check_heredoc(toklst);
				// display_toklst(toklst);
				executor(toklst, envlst);
				clear_heredoc(toklst);
			}
			free_toklst(toklst);
			// // system("leaks minishell > leaks_result; cat leaks_result | grep leaked && rm -rf leaks_result");
			free(line);
		}
		else
			break ;
	}
	close(g_fd);
	free_envlst(envlst);
	// system("leaks minishell > leaks_result; cat leaks_result | grep leaked && rm -rf leaks_result");
	return (0);
}
