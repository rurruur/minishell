/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _check.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 14:44:00 by jrim              #+#    #+#             */
/*   Updated: 2022/07/16 02:24:29 by jrim             ###   ########.fr       */
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
	if (!(sq_flag + dq_flag > 0))
		err_msg("quote");
	return (sq_flag + dq_flag > 0); // flag가 -1이면 quote가 안닫혔다는 의미
}

int	check_pretok(t_token *pretok)
{
	int flag;
	
	flag = 1;
	if (pretok->type == T_PIPE)
		flag = 0;
	while (pretok && flag == 1)
	{	
		if (pretok->type > T_OFF && (!pretok->next || pretok->next->type > T_OFF))
			flag = 0;
		pretok = pretok->next;
	}
	if (flag == 0)
		err_msg("pipe or RDR");
	return (flag);
}

void	check_empty(t_token *pretok)
{
	while (pretok)
	{
		if (pretok->next && pretok->next->str[0] == '\0')
			del_from_strlst(&pretok);
		else
			pretok = pretok->next;
	}
}