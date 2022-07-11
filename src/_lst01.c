/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _lst01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 00:30:47 by jrim              #+#    #+#             */
/*   Updated: 2022/07/11 12:54:43 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token		*init_strlst(char *content);
void		add_to_strlst(t_token **strlst, t_token *new);
void		del_from_strlst(t_token **strlst);
void		lst_to_lst(t_token **old, t_token **new);
void		free_strlst(t_token **strlst);

t_token		*init_strlst(char *content)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		err_msg("token allocation");
	new->str = content;
	new->type = OFF;
	new->next = NULL;
	return (new);
}

void	add_to_strlst(t_token **strlst, t_token *new)
{
	t_token *tmp;
	
	if (*strlst == NULL)
		(*strlst) = new;
	else
	{
		tmp = *strlst;
		while ((*strlst)->next)
			*strlst = (*strlst)->next;
		(*strlst)->next = new;
		*strlst = tmp;
	}
	// (*strlst)->size++;
}

void	del_from_strlst(t_token **strlst)
{
	t_token	*del;

	del = (*strlst)->next;
	(*strlst)->next = (*strlst)->next->next;
	del->next = NULL;
	free(del->str);
	free(del);
}

void	lst_to_lst(t_token **old, t_token **new)
{
	t_token	*tmp;

	tmp = (*old);
	(*old) = (*old)->next;
	tmp->next = NULL;
	add_to_strlst(new, tmp);
}

void	free_strlst(t_token **strlst)
{
	t_token	*tmp;

	while (*strlst)
	{
		tmp = (*strlst);
		(*strlst) = (*strlst)->next;
		free(tmp->str);
		tmp->str = NULL;
		tmp->next = NULL;
		free(tmp);
		tmp = NULL;
	}
	strlst = NULL;
}
