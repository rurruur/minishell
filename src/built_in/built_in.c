/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:35:25 by jrim              #+#    #+#             */
/*   Updated: 2022/07/15 00:21:32 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_main(char *cmd, t_token *argv)
{
	int	len;

	len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "cd", len))
		msh_cd(argv);
	else if (!ft_strncmp(cmd, "echo", len))
		msh_echo(argv);
	else if (!ft_strncmp(cmd, "env", len))
		msh_env(argv);
	else if (!ft_strncmp(cmd, "exit", len))
		msh_exit(argv);
	else if (!ft_strncmp(cmd, "pwd", len))
		msh_pwd();
	else if (!ft_strncmp(cmd, "unset", len))
		msh_unset(argv);
}