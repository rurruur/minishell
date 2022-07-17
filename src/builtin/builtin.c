/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:35:25 by jrim              #+#    #+#             */
/*   Updated: 2022/07/17 18:51:17 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_main(char *cmd, t_token *argv, t_env *envlst)
{
	int ret;

	ret = 0;
	if (!ft_strcmp(cmd, "cd"))
		ret = msh_cd(argv, envlst);
	else if (!ft_strcmp(cmd, "echo"))
		ret = msh_echo(argv);
	else if (!ft_strcmp(cmd, "env"))
		ret = msh_env(argv, envlst);
	else if (!ft_strcmp(cmd, "exit"))
		ret = msh_exit(argv);
	else if (!ft_strcmp(cmd, "pwd"))
		ret = msh_pwd(argv);
	else if (!ft_strcmp(cmd, "unset"))
		ret = msh_unset(argv, envlst);
	else if (!ft_strcmp(cmd, "export"))
		ret = msh_export(argv, envlst);
	return (ret);
}