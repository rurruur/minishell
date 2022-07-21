/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:35:25 by jrim              #+#    #+#             */
/*   Updated: 2022/07/21 18:34:34 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

enum e_builtin	get_builtin_type(t_token *cmd)
{
	if (cmd == NULL || ft_strlen(cmd->str) == 0)
		return NONE;
	if (!ft_strcmp(cmd->str, "cd"))
		return (CD);
	else if (!ft_strcmp(cmd->str, "echo"))
		return (ECHO);
	else if (!ft_strcmp(cmd->str, "env"))
		return (ENV);
	else if (!ft_strcmp(cmd->str, "exit"))
		return (EXIT);
	else if (!ft_strcmp(cmd->str, "pwd"))
		return (PWD);
	else if (!ft_strcmp(cmd->str, "unset"))
		return (UNSET);
	else if (!ft_strcmp(cmd->str, "export"))
		return (EXPORT);
	else
		return (NONE);
}

void	builtin_main(t_token *argv, t_env *envlst, enum e_builtin cmd)
{
	dprintf(g_fd, "builtin_main in\n");
	if (cmd == CD)
		msh_cd(argv, envlst);
	else if (cmd == ECHO)
		msh_echo(argv);
	else if (cmd == ENV)
		msh_env(argv, envlst);
	else if (cmd == EXIT)
		msh_exit(argv);
	else if (cmd == PWD)
		msh_pwd(argv);
	else if (cmd == UNSET)
		msh_unset(argv, envlst);
	else if (cmd == EXPORT)
		msh_export(argv, envlst);
}

void	builtin_error(char *err_msg)
{
	ft_putstr_fd("( ༎ຶД༎ຶ): ", STDERR_FILENO);
	ft_putstr_fd(err_msg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (errno <= MAX_ERRNO)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		dprintf(g_fd, "errno: %d\n", errno);
		g_status = errno;
		return ;
	}
	else if (errno == CMD_NOT_FOUND)
		ft_putendl_fd("command not found", STDERR_FILENO);
	else if (errno == IS_DIR)
		ft_putendl_fd("Is a directory", STDERR_FILENO);
	else if (errno == NO_EXIST)
		ft_putendl_fd("No such file or directory", STDERR_FILENO);
	g_status = errno - MAX_ERRNO;
}