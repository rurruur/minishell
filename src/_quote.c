/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:58:07 by jrim              #+#    #+#             */
/*   Updated: 2022/07/09 14:14:09 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_quote(char *line);
char	*trim_quote(char *str);
int		check_len(char *str);

int	check_quote(char *line)
{
	int	sq_flag;	// single quote flag
	int	dq_flag;	// double quote flag

	sq_flag = 1;
	dq_flag = 1;
	while (*line)
	{
		if (ft_strncmp(line, "\\'", 2) == 0 || ft_strncmp(line, "\\\"", 2) == 0)
		{
			line += 2;
			continue ;
		}
		if (dq_flag > 0 && *line == '\'')
			sq_flag = -sq_flag;
		if (sq_flag > 0 && *line == '"')
			dq_flag = -dq_flag;
		line++;
	}
	return (sq_flag + dq_flag > 0); // flag가 -1이면 quote가 안닫혔다는 의미
}

char	*trim_quote(char *str)
{
	int		new_len;
	int		idx;
	char	*new;

	new_len = check_len(str);
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