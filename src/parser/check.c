/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 14:44:00 by jrim              #+#    #+#             */
/*   Updated: 2022/07/17 16:06:27 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		check_whitespace(char *line);
int		check_quote(char *line);
int		check_pretok(t_token *pretok);
void	check_empty(t_token *pretok);

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
		if (ft_strncmp(line, "\\'", 2) == 0 || ft_strncmp(line, "\\\"", 2) == 0)
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
		err_custom(0, NULL);
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
		if (pretok->type > T_OFF && (!pretok->next || pretok->next->type > T_OFF))
		{
			flag = 0;
			break ;
		}
		pretok = pretok->next;
	}
	if (flag == 0 && pretok->type == T_PIPE)
		err_syntax(1, "|");
	else if (flag == 0 && pretok->type != T_PIPE && !pretok->next)
		err_syntax(2, pretok->str);
	else if (flag == 0 && pretok->type != T_PIPE)
		err_syntax(1, pretok->next->str);
	// 여기 이상해...
	return (flag);
}

void	check_empty(t_token *pretok)
{
	while (pretok)
	{
		if (pretok->str[0] == '\0')
			del_from_strlst(&pretok);
		else
			pretok = pretok->next;
	}
}
