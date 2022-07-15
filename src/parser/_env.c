/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 02:24:13 by jrim              #+#    #+#             */
/*   Updated: 2022/07/16 02:26:44 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	copy_env(char **env);
void	find_env(t_token *pretok);
char	*insert_env(char *old, int	start, int len, char *key);

void	find_env(t_token *pretok)
{
	char 	*str;
	char	*env_key;
	int		sq;
	int		start;
	int		len;

	while (pretok)
	{
		sq = CLOSED;
		str = pretok->str;
		start = 0;
		len = 0;
		while (*str)
		{
			if (*str == '\'')
				sq = -sq;
			if (sq == CLOSED && *str == '$')
			{
				str++;
				while (!ft_strchr(DELIM, str[len]) && str[len] != '\\')
					len++;
				env_key = ft_strndup(str, len);
				pretok->str = insert_env(pretok->str, start, len, env_key);
			}
			start++;
			str++;
		}
		pretok = pretok->next;
	}
}

char	*insert_env(char *old, int	start, int len, char *key)
{
	char	*new;
	char	*front;
	char	*env_val;
	char	*rear;

	front = ft_strndup(old, start);
	env_val = getenv(key);
	rear = ft_strdup(old + start + len + 1);
	new = ft_strjoin(front, env_val);
	new = ft_strjoin(new, rear);
	return (new);
}