/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _check.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 14:44:00 by jrim              #+#    #+#             */
/*   Updated: 2022/07/10 23:09:13 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_quote(char *line);
int			check_pretok(t_token *pretok);
void		check_type(t_token *pretok);

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

int			check_pretok(t_token *pretok)
{
	int flag;
	
	flag = 1;
	check_type(pretok);
	if (pretok->type == PIPE)
		flag = 0;
	while (pretok && flag == 1)
	{	
		if (pretok->type != OFF && pretok->next && pretok->next->type != OFF)
			flag = 0;
		// if (pretok->next == NULL || pretok->next->type == PIPE)
		// 	pretok->type = END;
		pretok = pretok->next;
	}
	if (flag == 0)
		err_msg("pipe or RDR");
	return (flag);
}

void	check_type(t_token *pretok)
{
	char	*str;

	while (pretok)
	{
		str = pretok->str;
		if (!ft_strncmp(str, ">", ft_strlen(str)))
			pretok->type = RDR_IN;
		else if (!ft_strncmp(str, ">>", ft_strlen(str)))
			pretok->type = RDR_HD;
		else if (!ft_strncmp(str, "<", ft_strlen(str)))
			pretok->type = RDR_OUT;
		else if (!ft_strncmp(str, "<<", ft_strlen(str)))
			pretok->type = RDR_AP;
		else if (!ft_strncmp(str, "|", ft_strlen(str)))
			pretok->type = PIPE;
		else
			pretok->type = OFF;
		pretok = pretok->next;
	}
}
