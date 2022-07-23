/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:59:23 by jrim              #+#    #+#             */
/*   Updated: 2022/07/23 16:04:11 by nakkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	single_builtin(t_toklst *toklst, t_env *envlst, enum e_builtin type)
{
	int	stdin;
	int	stdout;

	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	set_redirection(toklst);
	builtin_main(toklst->cmd, envlst, type);
	dup2(stdin, STDIN_FILENO);
	dup2(stdout, STDOUT_FILENO);
	if (type == EXIT && (g_status == 0 || g_status == 255))
		return (STOP);
	return (CONTINUE);
}

static int	process_input(char *line, t_env *envlst)
{
	t_toklst		*toklst;
	enum e_builtin	type;

	add_history(line);
	toklst = tokenizer(line, NULL, envlst);
	if (toklst && check_heredoc(toklst))
	{
		display_toklst(toklst);
		type = get_builtin_type(toklst->cmd, toklst);
		if (toklst->next == NULL && type)
		{
			if (single_builtin(toklst, envlst, type) == STOP)
				return (STOP);
		}
		else
			executor(toklst, envlst);
	}
	clear_heredoc(toklst);
	free_toklst(toklst);
	free(line);
	return (CONTINUE);
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_env	*envlst;

	(void)argv;
	handle_sig(READLINE);
	g_status = 0;
	envlst = copy_env(env, NULL);
	while (argc)
	{
		input = readline(PRMPT);
		if (input)
		{
			if (process_input(input, envlst) == STOP)
				break ;
		}
		else
		{
			printf("exit\n");
			break ;
		}
	}
	free_envlst(envlst);
	return (0);
}
