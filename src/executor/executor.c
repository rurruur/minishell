/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 23:03:49 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/25 10:51:44 by nakkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	validate_cmd(t_token *cmd)
{
	if (cmd == NULL)
		exit(0);
	if (*(cmd->str) == '\0')
	{
		errno = CMD_NOT_FOUND;
		ft_error("");
	}
}

void	child_process(t_toklst *list, t_env *envlst)
{
	char			*cmd;
	char			**cmd_arr;
	char			**env;
	enum e_builtin	type;

	check_files(list);
	set_redirection(list);
	validate_cmd(list->cmd);
	type = get_builtin_type(list->cmd, list);
	if (type)
	{
		builtin_main(list->cmd, envlst, type);
		exit(0);
	}
	if (list->cmd->str[ft_strlen(list->cmd->str) - 1] == '/')
	{
		errno = IS_DIR;
		ft_error(list->cmd->str);
	}
	get_valid_cmd_path(list->cmd->str, envlst, &cmd);
	cmd_arr = list_to_arr(list->cmd);
	env = envlst_to_arr(envlst);
	if (execve(cmd, cmd_arr, env) == -1)
		ft_error(list->cmd->str);
}

int	get_pipe_count(t_toklst *list)
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

void	fork_child(t_toklst *list, t_env *envlst)
{
	pid_t		child;

	child = fork();
	list->pid = child;
	if (child == -1)
		ft_error("fork");
	if (child == 0)
		child_process(list, envlst);
}

void	executor(t_toklst *list, t_env *envlst)
{
	t_toklst	*tmp;

	tmp = list;
	if (get_pipe_count(list) > 251)
	{
		ft_putendl_fd("gumshell: pipe: Too many open files", STDERR_FILENO);
		return ;
	}
	while (list)
	{
		list->pid = 0;
		if (pipe(list->end) == -1)
			ft_error("pipe");
		fork_child(list, envlst);
		close(list->end[1]);
		list = list->next;
	}
	ft_wait(tmp);
}
