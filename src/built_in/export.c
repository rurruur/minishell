/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:36:53 by jrim              #+#    #+#             */
/*   Updated: 2022/07/17 03:12:30 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	_export_valid_key(char *str)
{
	int	idx;
	
	idx = 0;
	if (ft_isdigit(str[idx]))
		return (0);
	while (str[idx] != '\0' && str[idx] != '=')
	{
		if (!ft_isalnum(str[idx]) && str[idx] != '_')
			return (0);
		idx++;
	}
	if (str[idx] == '=')
		return (idx);
	else
		return (0);
}

void	_export_valid(char *str, t_env *envlst)
{
	int		key_len;
	char	*env_key;
	char	*env_val;
	char	*tmp;

	key_len = _export_valid_key(str);
	if (!key_len)
	{
		printf("invalid key\n");
		return ;
	}
	env_key = ft_strndup(str, key_len);
	str += key_len + 1;
	env_val = ft_strdup(str);
	// A=   인 경우에는?
	if (!env_val)
	{
		printf("invalid val\n");
		free(env_key);
		return ;
	}
	if (find_env(envlst, env_key))
	{
		while (envlst)
		{
			if (!ft_strcmp(envlst->key, env_key)) //  ft_strcmp 만들기
			{
				env_val = ft_strdup(envlst->val);
				break;
			}
			envlst = envlst->next;
		}
		tmp = envlst->val;
		envlst->val = env_val;
		free(tmp);
	}
	else
		add_to_envlst(&envlst, init_envlst(env_key, env_val));
}

int	msh_export(t_token *argv, t_env *envlst)
{
	if (!argv->next)
	{
		printf("뭔가 잔뜩 뽑아야해?\n");
		return (1);
	}
	argv = argv->next;
	while (argv)
	{
		_export_valid(argv->str, envlst);
		argv = argv->next;
	}
	return (1);
}