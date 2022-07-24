/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:36:35 by jrim              #+#    #+#             */
/*   Updated: 2022/07/24 15:59:11 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	msh_env(t_token *argv, t_env *envlst)
{
	if (argv->next)
	{
		errno = NO_EXIST;
		builtin_error(ft_strjoin("env: ", argv->next->str));
		return ;
	}
	while (envlst)
	{
		if (envlst->val)
		{
			ft_putstr_fd(envlst->key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putendl_fd(envlst->val, STDOUT_FILENO);
		}
		envlst = envlst->next;
	}
}
