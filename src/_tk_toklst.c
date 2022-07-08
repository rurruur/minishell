/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tk_toklst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 00:30:47 by jrim              #+#    #+#             */
/*   Updated: 2022/07/08 15:33:36 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token		*init_token(char *content);
void		add_to_strlst(t_token **strlst, t_token *new);
// void		add_flag(t_token *new);
void		del_from_strlst(t_token *strlst);
t_toklst	*init_toklst(void);
void		add_to_toklst(t_toklst **toklst, t_toklst *new);

t_token		*init_token(char *content)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		err_msg("token allocation");
	new->str = content;
	new->size = 0;
	new->next = NULL;
	return (new);
}

void		add_to_strlst(t_token **strlst, t_token *new)
{
	t_token *tmp;
	
	// add_flag(new);
	if (*strlst == NULL)
		(*strlst) = new;
	else
	{
		// printf("in\n");		
		tmp = *strlst;
		while ((*strlst)->next)
			*strlst = (*strlst)->next;
		(*strlst)->next = new;
		*strlst = tmp;
	}
	(*strlst)->size++;
}

void		del_from_strlst(t_token *strlst)
{
	t_token *tmp;

	// 현재 -> 지울 노드 -> 그 다음
	tmp = strlst->next;
	strlst->next = strlst->next->next;
	free(tmp->str);
	free(tmp);
}

// void		add_flag(t_token *new)
// {
// 	if (new->str[0] == '<')
// 	{
// 		new->flag = 1;
// 		if (new->str[1] == '<')
// 			new->flag = 3;
// 	}
// 	else if (new->str[0] == '>')
// 	{
// 		new->flag = 2;
// 		if (new->str[1] == '>')
// 			new->flag = 4;
// 	}
// }

t_toklst	*init_toklst(void)
{
	t_toklst	*new;

	new = (t_toklst *)malloc(sizeof(t_toklst));
	if (!new)
		err_msg("token list allocation");
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
