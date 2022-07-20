/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 23:03:49 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/20 14:31:07 by nakkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	child_process(t_toklst *list, t_env *envlst)
{
	char			*cmd;
	char			**cmd_arr;
	char			**env;
	enum e_builtin	type;

	dprintf(g_fd, "execute: %s\n", list->cmd->str);
	set_redirection(list);
	if (*(list->cmd->str) == '\0')
	{
		errno = CMD_NOT_FOUND;
		ft_error("");
	}
	type = get_builtin_type(list->cmd->str);
	if (list->next == NULL && type)
	{
		builtin_main(list->cmd, envlst, type);
		exit(0);
	}
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
	handle_sig(SIG_WAIT);
	ft_wait();
	handle_sig(READLINE);
	while (tmp)
	{
		close(tmp->end[0]);
		tmp = tmp->next;
	}
}
