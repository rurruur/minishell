/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _token03.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:58:07 by jrim              #+#    #+#             */
/*   Updated: 2022/07/12 23:50:41 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trim_pretok(t_token *pretok);
char	*trim_quote(char *str);
int		cnt_trimmed_len(char *str);

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

	new_len = cnt_trimmed_len(str);
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

int		cnt_trimmed_len(char *str)
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
			if (dq == OPEN || (dq == CLOSED && sq == CLOSED))
			{
				dq = -dq;
				*str = '\0';
			}
			else	// sq == OPEN
				len++;
		}
		else if (*str == '\'')
		{
			if (sq == OPEN || (dq == CLOSED && sq == CLOSED))
			{
				sq = -sq;
				*str = '\0';
			}
			else	// dq == OPEN
				len++;
		}
		else if (*str == '\\')
		{
			if (dq == OPEN || sq == OPEN)
				len++;
			else
				*str = '\0';
			len++;
			str++;
		}
		else
			len++;
		str++;
	}
	return (len);
}
