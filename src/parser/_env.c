/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 02:24:13 by jrim              #+#    #+#             */
/*   Updated: 2022/07/16 13:19:46 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	copy_env(char **env);
void	find_env(t_token *pretok);
char	*insert_env(char *old, char *str, int start);

void	find_env(t_token *pretok)
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
				pretok->str = insert_env(pretok->str, ++str, start);
			start++;
			str++;
		}
		pretok = pretok->next;
	}
}

char	*insert_env(char *old, char *str, int start)
{
	int		len;
	char	*env_key;
	char	*new;

	len = 0;
	while (!ft_strchr(DELIM, str[len]) && str[len] != '\\')
		len++;
	env_key = ft_strndup(str, len);
	if (*env_key == '\0')
	{
		free(env_key);
		return (old);
	}
	new = msh_strjoin(ft_strndup(old, start), ft_strdup(getenv(env_key)));
	new = msh_strjoin(new, ft_strdup(old + start + len + 1));
	free(env_key);
	free(old);
	return (new);
}