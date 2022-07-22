/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 23:03:49 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/21 22:53:31 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	child_process(t_toklst *list, t_env *envlst)
{
	char			*cmd;
	char			**cmd_arr;
	char			**env;
	enum e_builtin	type;

	// dprintf(g_fd, "child process\n");
	set_redirection(list);
	if (list->cmd->str == NULL)
		exit(0);
	if (*(list->cmd->str) == '\0')
	{
		errno = CMD_NOT_FOUND;
		ft_error("");
	}
	type = get_builtin_type(list->cmd, list);
	if (type)
	{
		builtin_main(list->cmd, envlst, type);
		exit(0);
	}
	cmd = get_valid_cmd_path(list->cmd->str, envlst);
	cmd_arr = list_to_arr(list->cmd);
	env = envlst_to_arr(envlst);
	if (execve(cmd, cmd_arr, env) == -1)
	{
		free(cmd);
		destroy_split(cmd_arr);
		destroy_split(env);
		ft_error(list->cmd->str);
	}
}

static int	get_pipe_count(t_toklst *list)
{
	int	count;

	count = 0;
	while (list)
	{
		count++;
		list = list->next;
	}
	return (count);
}

void	executor(t_toklst *list, t_env *envlst)
{
	t_toklst	*tmp;
	pid_t	child;

	tmp = list;
	if (get_pipe_count(list) > 250)
	{
		// errno = 24;	// Too many open files
		ft_putendl_fd("( ༎ຶД༎ຶ): pipe: Too many open files", STDERR_FILENO);
		// ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return ;
	}
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
