/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 00:30:47 by jrim              #+#    #+#             */
/*   Updated: 2022/07/17 16:30:55 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token		*init_strlst(char *content);
void		add_to_strlst(t_token **strlst, t_token *new);
void		del_from_strlst(t_token **strlst);
void		lst_to_lst(t_token **old, t_token **new);
void		free_strlst(t_token *strlst);

t_token	*init_strlst(char *content)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		err_alloc();
	new->str = content;
	new->type = T_OFF;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	add_to_strlst(t_token **strlst, t_token *new)
{
	t_token	*tmp;

	if (*strlst == NULL)
		(*strlst) = new;
	else
	{
		tmp = *strlst;
		while ((*strlst)->next)
			*strlst = (*strlst)->next;
		(*strlst)->next = new;
		new->prev = (*strlst);
		*strlst = tmp;
	}
}

// 현재 가리키고 있는 노드를 지우고 싶을 때
void	del_from_strlst(t_token **strlst)
{
	t_token	*del;
	t_token	*tmp;

	del = (*strlst);
	if ((*strlst)->prev == NULL) // 제일 앞 노드
	{
		(*strlst) = (*strlst)->next;
		(*strlst)->prev = NULL;
	}	
	else if ((*strlst)->next == NULL) // 제일 뒤 노드
	{
		(*strlst) = (*strlst)->prev;
		(*strlst)->next = NULL;
	}
	else
	{
		(*strlst) = (*strlst)->next;
		tmp = (*strlst)->prev;
		(*strlst)->prev = tmp;
		tmp->next = (*strlst);
	}
	free(del->str);
	del->next = NULL;
	del->prev = NULL;
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

void	free_strlst(t_token *strlst)
{
	t_token	*tmp;

	while (strlst)
	{
		tmp = strlst;
		strlst = strlst->next;
		free(tmp->str);
		tmp->str = NULL;
		tmp->next = NULL;
		free(tmp);
		tmp = NULL;
	}
}