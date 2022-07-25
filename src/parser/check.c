/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 14:44:00 by jrim              #+#    #+#             */
/*   Updated: 2022/07/23 00:21:17 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		check_whitespace(char *line);
int		check_quote(char *line);
int		check_pretok(t_token *pretok);

int	check_whitespace(char *line)
{
	while (*line)
	{
		if (!ft_strchr(WH_SPACE, *line))
			return (0);
		line++;
	}
	return (1);
}

int	check_quote(char *line)
{
	int	sq;
	int	dq;

	sq = CLOSED;
	dq = CLOSED;
	while (*line)
	{
		if (ft_strncmp(line, "\\\\", 2) == 0 || \
			ft_strncmp(line, "\\'", 2) == 0 || \
			ft_strncmp(line, "\\\"", 2) == 0)
		{
			line += 2;
			continue ;
		}
		if (dq == CLOSED && *line == '\'')
			sq = -sq;
		if (sq == CLOSED && *line == '"')
			dq = -dq;
		line++;
	}
	if (!(sq + dq > 0))
		err_parser(ERR_QUOTE);
	return (sq + dq > 0);
}

int	check_pretok(t_token *pretok)
{
	int	flag;

	flag = 1;
	if (pretok->type == T_PIPE)
		flag = 0;
	while (pretok && flag == 1)
	{	
		if (pretok->type == T_PIPE && !pretok->next)
			flag = 0;
		else if (pretok->type > T_PIPE && \
				(!pretok->next || pretok->next->type >= T_PIPE))
			flag = 0;
		pretok = pretok->next;
	}
	if (flag != 1)
		err_parser(ERR_SYNTAX);
	return (flag);
}
