/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env01.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 02:24:13 by jrim              #+#    #+#             */
/*   Updated: 2022/07/25 12:44:52 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*copy_env(char **env, t_env *envlst);
void	env_to_str(t_token *pretok, t_env *envlst);
void	skip_quote(char *str, int *idx, int *sq);
char	*insert_env(t_env *envlst, char *old, char *str);
char	**envlst_to_arr(t_env *envlst);

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
		new = init_envlst(msh_strndup(env[idx], delim), \
						msh_strdup(env[idx] + delim + 1));
		add_to_envlst(&envlst, new);
		idx++;
	}
	change_env_val(envlst, "OLDPWD", NULL);
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
		str = msh_strdup(pretok->str);
		idx = -1;
		while (str[++idx])
		{
			skip_quote(str, &idx, &sq);
			if (sq == CLOSED && str[idx] == '$')
			{
				pretok->type = T_ENV;
				pretok->str = insert_env(envlst, pretok->str, str + idx);
			}
		}
		pretok = pretok->next;
		free(str);
	}
}

void	skip_quote(char *str, int *idx, int *sq)
{
	if ((*idx) == 0 && str[(*idx)] == '\'')
		(*sq) = -(*sq);
	else if (ft_strchr("\\$\"", str[(*idx)]) == 0 \
			&& str[(*idx) + 1] == '\'')
	{
		(*idx)++;
		(*sq) = -(*sq);
	}
	else if ((*sq) == CLOSED && str[(*idx)] == '$')
		return ;
	else
		(*idx)++;
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
	dollar = 0;
	while (old[dollar] && old[dollar] != '$')
		dollar++;
	if (key_len == 0 && ft_strcmp(old + dollar, "$") == 0)
	{
		free(env_key);
		return (old);
	}
	env_val = get_env_val(envlst, env_key);
	if (old[dollar] == '$' && old[dollar + 1] && old[dollar + 1] == '$')
		dollar++;
	new = msh_strjoin(msh_strndup(old, dollar), env_val);
	new = msh_strjoin(new, msh_strdup(old + dollar + key_len + 1));
	free(old);
	free(env_key);
	return (new);
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
	if (!arr)
		err_alloc();
	arr[size] = NULL;
	size = 0;
	while (envlst)
	{
		arr[size++] = double_strjoin(envlst->key, "=", envlst->val);
		envlst = envlst->next;
	}
	return (arr);
}
