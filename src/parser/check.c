/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 14:44:00 by jrim              #+#    #+#             */
/*   Updated: 2022/07/24 16:18:15 by jrim             ###   ########.fr       */
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
			return (INVALID);
		line++;
	}
	return (VALID);
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

	flag = VALID;
	if (pretok->type == T_PIPE)
		flag = INVALID;
	while (pretok && flag == VALID)
	{	
		if (pretok->type == T_PIPE && !pretok->next)
			flag = INVALID;
		else if (pretok->type > T_PIPE && \
				(!pretok->next || pretok->next->type >= T_PIPE))
			flag = INVALID;
		pretok = pretok->next;
	}
	if (flag != VALID)
		err_parser(ERR_SYNTAX);
	return (flag);
}
