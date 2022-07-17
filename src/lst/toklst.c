/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toklst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 00:30:47 by jrim              #+#    #+#             */
/*   Updated: 2022/07/17 16:29:43 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_toklst	*init_toklst(t_env *envlst);
void		add_to_toklst(t_toklst **toklst, t_toklst *new);
void		free_toklst(t_toklst *toklst);

t_toklst	*init_toklst(t_env *envlst)
{
	t_toklst	*new;

	new = (t_toklst *)malloc(sizeof(t_toklst));
	if (!new)
		err_alloc();
	new->cmd = NULL;
	new->rdr_in = NULL;
	new->rdr_out = NULL;
	new->envlst = envlst;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	add_to_toklst(t_toklst **toklst, t_toklst *new)
{
	t_toklst	*tmp;

	if (*toklst == NULL)
		(*toklst) = new;
	else
	{
		tmp = *toklst;
		while ((*toklst)->next)
			*toklst = (*toklst)->next;
		(*toklst)->next = new;
		new->prev = (*toklst);
		*toklst = tmp;
	}
}

void	free_toklst(t_toklst *toklst)
{
	t_toklst	*tmp;

	while (toklst)
	{
		tmp = toklst;
		toklst = toklst->next;
		free_strlst(tmp->cmd);
		free_strlst(tmp->rdr_in);
		free_strlst(tmp->rdr_out);
		free(tmp);
		tmp = NULL;
	}
}
