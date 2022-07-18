/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:35:25 by jrim              #+#    #+#             */
/*   Updated: 2022/07/18 21:17:24 by nakkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_main(char *cmd, t_token *argv, t_env *envlst)
{
	if (!ft_strcmp(cmd, "cd"))
		msh_cd(argv, envlst);
	else if (!ft_strcmp(cmd, "echo"))
		msh_echo(argv);
	else if (!ft_strcmp(cmd, "env"))
		msh_env(argv, envlst);
	else if (!ft_strcmp(cmd, "exit"))
		msh_exit(argv);
	else if (!ft_strcmp(cmd, "pwd"))
		msh_pwd(argv);
	else if (!ft_strcmp(cmd, "unset"))
		msh_unset(argv, envlst);
	else if (!ft_strcmp(cmd, "export"))
		msh_export(argv, envlst);
	else
		return ;
	exit(0);
}