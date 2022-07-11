/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _token03.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:58:07 by jrim              #+#    #+#             */
/*   Updated: 2022/07/11 15:06:29 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trim_pretok(t_token *pretok);
char	*trim_quote(char *str, int *quote);
int		check_len(char *str);

void	trim_pretok(t_token *pretok)
{
	char	*new;
	char	*tmp;
	t_token	*ptr;
	int		quote;

	ptr = pretok;
	while (pretok)
	{
		quote = 0;
		tmp = pretok->str;
		new = trim_quote(pretok->str, &quote);
		if (quote == 1)
		{
			pretok->str = new;
			free(tmp);
		}
		tmp = NULL;
		pretok = pretok->next;
	}
	pretok = ptr;
	while (pretok)
	{
		if (pretok->next && pretok->next->str[0] == '\0')
			del_from_strlst(&pretok);
		else
			pretok = pretok->next;
	}
}

char	*trim_quote(char *str, int *quote)
{
	int		old_len;
	int		new_len;
	int		idx;
	char	*new;

	old_len = ft_strlen(str);
	new_len = check_len(str);
	if (old_len == new_len)
		return (str);
	idx = 0;
	*quote = 1;
	new = (char	*)malloc((new_len + 1) * sizeof(char));
	while (idx < new_len)
	{
		if (*str != '\0')
		{
			new[idx] = *str;
			idx++;
		}
		str++;
	}
	new[idx] = '\0';
	return (new);
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