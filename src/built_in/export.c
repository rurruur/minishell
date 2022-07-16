/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:36:53 by jrim              #+#    #+#             */
/*   Updated: 2022/07/16 21:43:46 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	_export_valid(char *str)
{
	if (*str == '=')
	{
		printf("minishell: export: `%c': not a valid identifier\n", *str);
		return (0);
	}
	while (*str)
	{
		if (ft_isdigit(*str))
		{
			printf("minishell: export: `%c': not a valid identifier\n", *str);
			return (0);
		}
		str++;
	}
	return (1);
}

int	msh_export(t_token *argv, t_env *envlst)
{
	if (!argv->next)
	{
		printf("뭔가 잔뜩 뽑아야해\n");
		return (1);
	}
	argv = argv->next;
	if (envlst)
		printf("아직이야\n");
	// while (argv)
	// {
	// 	// 먼저 유효한 조합인지 확인 -> A=a (공백 없이)
	// 	// 유효한 경우만 실행하되
	// 	// 이미 있는 경우 val을 바꿔줘야함
	// 	// 없는 경우에는 새로 만들어야함
	// 	argv = argv->next;
	// }
	return (0);
}