/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:36:35 by jrim              #+#    #+#             */
/*   Updated: 2022/07/21 18:17:57 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	msh_env(t_token *argv, t_env *envlst)
{
	(void)argv;
	if (!envlst || argv->next)
		return (0);
	while (envlst)
	{
		if (envlst->val)
			printf("%s=%s\n", envlst->key, envlst->val);
		envlst = envlst->next;
	}
	return (1);
}
