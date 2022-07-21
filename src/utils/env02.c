/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env02.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 02:24:13 by jrim              #+#    #+#             */
/*   Updated: 2022/07/21 18:23:10 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_key(char *str);
char	*get_env_val(t_env *envlst, char *key);
int		find_env_val(t_env *envlst, char *key);
int		change_env_val(t_env *envlst, char *key, char *new_val);
char	**envlst_to_arr(t_env *envlst);

char	*get_env_key(char *str)
{
	int		idx;
	int		key_len;
	char	*env_key;

	idx = 1;
	key_len = 0;
	while (str[idx])
	{
		if (idx == 1 && ft_isdigit(str[1]))
		{
			key_len++;
			break ;
		}
		else if (!ft_isalnum(str[idx]) && str[idx] != '_')
			break ;
		key_len++;
		idx++;
	}
	if (str[1] == '?')
		key_len = 1;
	env_key = ft_strndup(str + 1, key_len);
	return (env_key);
}

char	*get_env_val(t_env *envlst, char *key)
{
	char	*env_val;

	env_val = NULL;
	if (*key == '?')
		return (ft_itoa(g_status));
	while (envlst)
	{
		if (!ft_strcmp(envlst->key, key) && envlst->val)
		{
			env_val = ft_strdup(envlst->val);
			break ;
		}
		envlst = envlst->next;
	}
	return (env_val);
}

int		find_env_val(t_env *envlst, char *key)
{
	int	flag;

	flag = 0;
	while (envlst)
	{
		if (!ft_strcmp(envlst->key, key))
		{
			flag = 1;
			break ;
		}
		envlst = envlst->next;
	}
	return (flag);
}

int	change_env_val(t_env *envlst, char *key, char *new_val)
{
	char	*tmp;

	while (envlst)
	{
		if (!ft_strcmp(envlst->key, key))
			break ;
		envlst = envlst->next;
	}
	if (!envlst)
		return (0);
	tmp = envlst->val;
	envlst->val = new_val;
	if (tmp)
		free(tmp);
	return (1);
}

char	**envlst_to_arr(t_env *envlst)
{
	char	**arr;
	int		size;
	t_env	*tmp;

	tmp = envlst;
	size = 0;
	while (tmp)
	{
		tmp = tmp->next;
		size++;
	}
	arr = (char **)malloc(sizeof(char *) * (size + 1));
	arr[size] = NULL;
	size = 0;
	while (envlst)
	{
		arr[size++] = double_strjoin(envlst->key, "=", envlst->val);
		envlst = envlst->next;
	}
	return (arr);
}
