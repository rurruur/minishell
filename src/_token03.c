/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _token03.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:58:07 by jrim              #+#    #+#             */
/*   Updated: 2022/07/11 19:02:31 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trim_pretok(t_token *pretok);
char	*trim_quote(char *str);
int		check_len(char *str);

void	trim_pretok(t_token *pretok)
{
	char	*new;
	char	*tmp;

	while (pretok)
	{
		tmp = pretok->str;
		new = trim_quote(pretok->str);
		if (new)
		{
			pretok->str = new;
			free(tmp);
		}
		tmp = NULL;
		pretok = pretok->next;
	}
}

char	*trim_quote(char *str)
{
	int		new_len;
	int		idx;
	char	*new_str;

	new_len = check_len(str);
	if (new_len == (int)ft_strlen(str))
		return (NULL);
	idx = 0;
	new_str = (char	*)malloc((new_len + 1) * sizeof(char));
	if (!new_str)
		err_msg("allocation");
	while (idx < new_len)
	{
		if (*str != '\0')
			new_str[idx++] = *str;
		str++;
	}
	new_str[idx] = '\0';
	return (new_str);
}

int		check_len(char *str)
{
	int	len;
	int	dq;
	int	sq;

	len = 0;
	dq = CLOSED;
	sq = CLOSED;
	while (*str)
	{
		if (*str == '"')
		{
			if (dq == CLOSED && sq == CLOSED)
			{
				dq = OPEN;
				*str = '\0';
			}
			else if (dq == OPEN)
			{
				dq = CLOSED;
				*str = '\0';
			}
			else if (sq == OPEN)
				len++;
			else 
				len++;
		}
		else if (*str == '\'')
		{
			if (dq == CLOSED && sq == CLOSED)
			{
				sq = OPEN;
				*str = '\0';
			}
			else if (sq == OPEN)
			{
				sq = CLOSED;
				*str = '\0';
			}
			else if (dq == OPEN)
				len++;
			else 
				len++;
		}
		else if (*str == '\\')
		{
			if (dq == OPEN || sq == OPEN)
			{
				str++;
				len += 2;
			}
			else
			{
				*str = '\0';
				str++;
				len++;
			}
		}
		else
			len++;
		str++;
	}
	return (len);
}
