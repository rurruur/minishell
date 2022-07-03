/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _check.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 17:01:52 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/03 17:21:24 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote(char *line);

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
			continue;
		}
		if (dq_flag > 0 && *line == '\'')
			sq_flag = -sq_flag;
		if (sq_flag > 0 && *line == '"')
			dq_flag = -dq_flag;
		line++;
	}
	return (sq_flag + dq_flag > 0); // flag가 -1이면 quote가 안닫혔다는 의미
}
