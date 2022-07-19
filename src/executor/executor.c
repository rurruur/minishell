/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 23:03:49 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/19 22:56:28 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	child_process(t_toklst *list, t_env *envlst)
{
	char	*cmd;
	char	**cmd_arr;
	char	**env;

	set_redirection(list);
	if (*(list->cmd->str) == '\0')
	{
		errno = CMD_NOT_FOUND;
		ft_error("");
	}
	builtin_main(list->cmd->str, list->cmd, envlst);
	cmd = get_valid_cmd_path(list->cmd->str, envlst);
	cmd_arr = list_to_arr(list->cmd);
	env = envlst_to_arr(envlst);
	close(list->end[0]);
	close(list->end[1]);
	if (execve(cmd, cmd_arr, env) == -1)
	{
		free(cmd);
		destroy_split(cmd_arr);
		destroy_split(env);
		ft_error(list->cmd->str);
	}
}

void	executor(t_toklst *list, t_env *envlst)
{
	t_toklst	*tmp;
	pid_t	child;

	tmp = list;
	while (list)
	{
		if (pipe(list->end) == -1)
			ft_error("pipe");
		child = fork();
		if (child == -1)
			ft_error("fork");
		if (child == 0)
			child_process(list, envlst);
		close(list->end[1]);
		list = list->next;
	}
	ft_wait();
	while (tmp)
	{
		close(tmp->end[0]);
		tmp = tmp->next;
	}
}
