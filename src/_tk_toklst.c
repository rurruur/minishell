/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tk_toklst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 00:30:47 by jrim              #+#    #+#             */
/*   Updated: 2022/07/06 18:13:53 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token		*init_token(void);
void		add_to_strlst(t_token **strlst, t_token *new);
t_toklst	*init_toklst(void);
void		add_to_toklst(t_toklst **toklst, t_toklst *new);

t_token		*init_token(void)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		errmsg("token allocation");
	new->str = NULL;
	new->next = NULL;
}

void		add_to_strlst(t_token **strlst, t_token *new)
{
	if (*strlst == NULL)
		(*strlst) = new;
	else
	{
		while ((*strlst)->next)
			*strlst = (*strlst)->next;
		(*strlst)->next = new;
	}
}

t_toklst	*init_toklst(void)
{
	t_toklst	*new;

	new = (t_toklst *)malloc(sizeof(t_toklst));
	if (!new)
		errmsg("token list allocation");
	new->cmd = NULL;
	new->infile = NULL;
	new->outfile = NULL;
	new->heredoc = NULL;
	new->append = NULL;
	new->next = NULL;
	return (new);
}

void	add_to_toklst(t_toklst **toklst, t_toklst *new)
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
