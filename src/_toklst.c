/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _toklst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 00:30:47 by jrim              #+#    #+#             */
/*   Updated: 2022/07/05 22:28:46 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *trim_pretok(char **pretok, int *idx, t_toknd *toklst);
t_toknd	*init_toknd(t_token *content);
void	add_token(t_toknd **toklst, t_toknd *new);

t_token *trim_pretok(char **pretok, int *idx, t_toknd *toklst)
{
	t_token *content;

	while (pretok[*idx] && pretok[*idx][0] != '|')
	{
		if (pretok[*idx][0] == '<' || pretok[*idx][0] == '>')
		{
			// redirection 종류 구분해서 넣아야함.
		}
		else if (pretok[*idx][0] == '\'' || pretok[*idx][0] == '"')
		{
			//trim_quote
		}
		else
		{
			// 일반 cmd인지, param인지에 따라 다름
		}
		(*idx)++;
	}
	return (content);
}

t_toknd	*init_toknd(t_token *content)
{
	t_toknd	*new;

	new = (t_toknd *)malloc(sizeof(t_toknd));
	new->content = content;
	return (new);
}

void	add_token(t_toknd **toklst, t_toknd *new)
{
	if (*toklst == NULL)
		(*toklst) = new;
	else
	{
		while ((*toklst)->next)
			*toklst = (*toklst)->next;
		(*toklst)->next = new;
	}
}
