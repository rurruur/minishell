/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:35:25 by jrim              #+#    #+#             */
/*   Updated: 2022/07/21 12:39:20 by nakkim           ###   ########.fr       */
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
