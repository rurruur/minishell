/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:35:25 by jrim              #+#    #+#             */
/*   Updated: 2022/07/16 21:44:12 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_main(char *cmd, t_token *argv, t_env *envlst)
{
	int	len;
	int ret;

	len = ft_strlen(cmd);
	ret = 0;
	if (!ft_strncmp(cmd, "cd", len))
		ret = msh_cd(argv, envlst);
	else if (!ft_strncmp(cmd, "echo", len))
		ret = msh_echo(argv);
	else if (!ft_strncmp(cmd, "env", len))
		ret = msh_env(argv, envlst);
	else if (!ft_strncmp(cmd, "exit", len))
		ret = msh_exit(argv);
	else if (!ft_strncmp(cmd, "pwd", len))
		ret = msh_pwd(argv);
	else if (!ft_strncmp(cmd, "unset", len))
		ret = msh_unset(argv, envlst);
	else if (!ft_strncmp(cmd, "export", len))
		ret = msh_export(argv, envlst);
	dprintf(g_fd, "ret from built in: %d\n", ret);
	return (ret);
}