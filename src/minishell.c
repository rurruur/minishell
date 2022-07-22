/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:59:23 by jrim              #+#    #+#             */
/*   Updated: 2022/07/22 14:56:02 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_env		*envlst;
	t_toklst	*toklst;
	enum e_builtin	type;

	(void)argv;
	handle_sig(READLINE);
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
				type = get_builtin_type(toklst->cmd, toklst);
				dprintf(g_fd, "type: %d\n", type);
				if (toklst->next == NULL && type)
				{
					dprintf(g_fd, "single builtin\n");
					if (check_heredoc(toklst))
					{
						int stdin = dup(STDIN_FILENO);
						int stdout = dup(STDOUT_FILENO);
						set_redirection(toklst);
						builtin_main(toklst->cmd, envlst, type);
						dup2(stdin, STDIN_FILENO);
						dup2(stdout, STDOUT_FILENO);
						if (type == EXIT && (g_status == 0 || g_status == 255))
							break ;
					}
				}
				else
				{
					dprintf(g_fd, "executor\n");
					// display_toklst(toklst);
					if (check_heredoc(toklst))
					{
						// display_toklst(toklst);
						executor(toklst, envlst);
					}
					// display_envlst(envlst);
				}
			}
			clear_heredoc(toklst);
			free_toklst(toklst);
			// printf("------------\n");
			// system("leaks minishell > leaks_result; cat leaks_result | grep leaked && rm -rf leaks_result");
			free(line);
		}
		else
		{
			printf("exit\n");
			break ;
		}
	}
	close(g_fd);
	free_envlst(envlst);
	// system("leaks minishell > leaks_result; cat leaks_result | grep leaked && rm -rf leaks_result");
	return (0);
}
