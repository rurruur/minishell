/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env02.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 02:24:13 by jrim              #+#    #+#             */
/*   Updated: 2022/07/17 15:53:29 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_key(char *str);

char	*get_env_key(char *str)
{
	int		idx;
	int		key_len;
	char	*env_key;
	// $로 시작하지만 뒤에는 뭐가오는지 모르는 str이 들어왔다고 가정하자.
	// *str == '$'
	idx = 1;
	key_len = 0;
	while (str[idx])
	{
		if (!ft_isalnum(str[idx]) && str[idx] != '_')
			break ;
		key_len++;
		idx++;
	}
	env_key = ft_strndup(str + 1, key_len);
	return (env_key);
}