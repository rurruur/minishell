/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token03.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:58:07 by jrim              #+#    #+#             */
/*   Updated: 2022/07/23 00:23:55 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	trim_pretok(t_token *pretok);
char	*trim_quote(char *str);
int		cnt_trimmed_len(char *str);
void	del_quote_or_escape(char **str, int *q1, int *q2, int *len);

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
	new_str = (char *)malloc((new_len + 1) * sizeof(char));
	if (!new_str)
		err_alloc();
	while (idx < new_len)
	{
		if (*str != '\0')
			new_str[idx++] = *str;
		str++;
	}
	new_str[idx] = '\0';
	return (new_str);
}

int	cnt_trimmed_len(char *str)
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
			del_quote_or_escape(&str, &dq, &sq, &len);
		else if (*str == '\'')
			del_quote_or_escape(&str, &sq, &dq, &len);
		else if (ft_strncmp(str, "\\\\", 2) == 0)
		{
			*(++str) = '\0';
			len++;
		}
		else if (*str == '\\')
			del_quote_or_escape(&str, &dq, &sq, &len);
		else
			len++;
		str++;
	}
	return (len);
}

void	del_quote_or_escape(char **str, int *q1, int *q2, int *len)
{
	if (**str == '\\')
	{
		if (*q1 == CLOSED && *q2 == CLOSED && *(*str + 1) != '\0')
			(**str) = '\0';
		else if (*q1 == OPEN || *q2 == OPEN)
			(*len)++;
		(*len)++;
		(*str)++;
		return ;
	}
	if (*q1 == OPEN || (*q1 == CLOSED && *q2 == CLOSED))
	{
		(*q1) = -(*q1);
		(**str) = '\0';
	}
	else
		(*len)++;
}
