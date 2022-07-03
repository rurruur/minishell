/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _check.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 17:01:52 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/03 17:04:03 by nakkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote(char *line);

int	check_quote(char *line)
{
	int	flag;

	flag = 1;
	while (*line)
	{
		if (ft_strncmp(line, "\\'", 2) == 0)
		{
			line += 2;
			continue;
		}
		if (*line == '\'')
			flag = -flag;
		line++;
	}
	return (flag > 0);
}
