/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _lst02.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 00:30:47 by jrim              #+#    #+#             */
/*   Updated: 2022/07/11 14:57:24 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_toklst	*init_toklst(void);
void		add_to_toklst(t_toklst **toklst, t_toklst *new);
void		free_toklst(t_toklst **toklst);

t_toklst	*init_toklst(void)
{
	t_toklst	*new;

	new = (t_toklst *)malloc(sizeof(t_toklst));
	if (!new)
		err_msg("token list allocation");
	new->cmd = NULL;
	new->rdr = NULL;
	new->infile = NULL;
	new->heredoc = NULL;
	new->outfile = NULL;
	new->append = NULL;
	new->next = NULL;
	return (new);
}

void	add_to_toklst(t_toklst **toklst, t_toklst *new)
{
	t_toklst *tmp;

	if (*toklst == NULL)
		(*toklst) = new;
	else
	{
		tmp = *toklst;
		while ((*toklst)->next)
			*toklst = (*toklst)->next;
		(*toklst)->next = new;
		*toklst = tmp;
	}
}

void		free_toklst(t_toklst **toklst)
{
	t_toklst	*tmp;

	while (*toklst)
	{
		tmp = (*toklst);
		(*toklst) = (*toklst)->next;
		free_strlst(&(tmp->cmd));
		free_strlst(&(tmp->infile));
		free_strlst(&(tmp->outfile));
		free_strlst(&(tmp->heredoc));
		free_strlst(&(tmp->append));
		free(tmp);
		tmp = NULL;
	}
	toklst = NULL;
}