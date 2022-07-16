/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 02:24:13 by jrim              #+#    #+#             */
/*   Updated: 2022/07/16 21:07:46 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*copy_env(char **env, t_env *envlst);
void	is_env(t_token *pretok, t_env *envlst);
char	*insert_env(t_env *envlst, char *old, char *str, int start);
char	*find_env(t_env *envlst, char *key);
char	**get_env(t_env *envlst);

t_env	*copy_env(char **env, t_env *envlst)
{
	int		idx;
	int 	delim;
	t_env	*new;

	idx = 0;
	while (env[idx])
	{
		delim = 0;
		while (env[idx][delim] != '=')
			delim++;
		new = init_envlst(ft_strndup(env[idx], delim), ft_strdup(env[idx] + delim + 1));
		add_to_envlst(&envlst, new);
		idx++;
	}
	return (envlst);
}

void	is_env(t_token *pretok, t_env *envlst)
{
	char 	*str;
	int		sq;
	int		start;

	while (pretok)
	{
		sq = CLOSED;
		str = pretok->str;
		start = 0;
		while (*str)
		{
			if (*str != '\\' && *(str + 1) == '\'')
			{
				sq = -sq;
				str++;
			}
			else if (sq == CLOSED && *str == '$')
				pretok->str = insert_env(envlst, pretok->str, ++str, start);
			start++;
			str++;
		}
		pretok = pretok->next;
	}
}

char	*insert_env(t_env *envlst, char *old, char *str, int start)
{
	int		len;
	char	*env_key;
	char	*env_val;
	char	*new;

	len = 0;
	while (!ft_strchr(DELIM, str[len]) && str[len] != '\\')
		len++;
	env_key = ft_strndup(str, len);
	env_val = find_env(envlst, env_key);
	free(env_key);
	if (len == 0)
		return (old);
	new = msh_strjoin(ft_strndup(old, start), env_val);
	new = msh_strjoin(new, ft_strdup(old + start + len + 1));
	free(old);
	return (new);
}

char	*find_env(t_env *envlst, char *key)
{
	char *env_val;

	env_val = NULL;
	while (envlst)
	{
		if (!ft_strncmp(envlst->key, key, ft_strlen(key)))
		{
			env_val = ft_strdup(envlst->val);
			break;
		}
		envlst = envlst->next;
	}
	return (env_val);
}

char	**get_env(t_env *envlst)
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