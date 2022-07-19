/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env01.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 02:24:13 by jrim              #+#    #+#             */
/*   Updated: 2022/07/20 00:01:36 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*copy_env(char **env, t_env *envlst);
void	env_to_str(t_token *pretok, t_env *envlst);
char	*insert_env(t_env *envlst, char *old, char *str);

t_env	*copy_env(char **env, t_env *envlst)
{
	int		idx;
	int		delim;
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

void	env_to_str(t_token *pretok, t_env *envlst)
{
	char	*str;
	int		idx;
	int		sq;

	while (pretok)
	{
		sq = CLOSED;
		str = ft_strdup(pretok->str);
		idx = -1;
		while (str[++idx])
		{
			if (str[idx] != '\\' && str[idx + 1] == '\'')
				sq = -sq;
			else if (sq == CLOSED && str[idx] == '$')
			{
				pretok->type = T_ENV;
				pretok->str = insert_env(envlst, pretok->str, str + idx);
			}
		}
		pretok = pretok->next;
		free(str);
	}
}

char	*insert_env(t_env *envlst, char *old, char *str)
{
	int		key_len;
	int		dollar;
	char	*env_key;
	char	*env_val;
	char	*new;

	env_key = get_env_key(str);
	key_len = (int)ft_strlen(env_key);
	if (key_len == 0)
	{
		free(env_key);
		return (old);
	}
	env_val = get_env_val(envlst, env_key);
	dollar = 0;
	while (old[dollar] && old[dollar] != '$')
		dollar++;
	new = msh_strjoin(ft_strndup(old, dollar), env_val);
	new = msh_strjoin(new, ft_strdup(old + dollar + key_len + 1));
	free(old);
	free(env_key);
	return (new);
}
