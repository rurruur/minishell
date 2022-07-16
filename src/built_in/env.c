/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:36:35 by jrim              #+#    #+#             */
/*   Updated: 2022/07/16 17:25:05 by nakkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	msh_env(t_token *argv, t_env *envlst)
{
	// 옵션이 있는지 없는지 검사?

	(void)argv;	
	while (envlst)
	{
		printf("%s=%s\n", envlst->key, envlst->val);
		envlst = envlst->next;
	}
}