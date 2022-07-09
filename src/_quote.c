/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _quote.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:58:07 by jrim              #+#    #+#             */
/*   Updated: 2022/07/09 14:01:49 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_quote(char *str);
int		check_len(char *str);

char	*trim_quote(char *str)
{
	// int		old_len;
	int		new_len;
	int		idx;
	char	*new;

	// old_len = ft_strlen(str);
	new_len = check_len(str);
	// printf("%d -> %d\n", old_len, new_len);
	idx = 0;
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

// "hello 'world'" 같은 경우는 안에 있는 '를 살려야함
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