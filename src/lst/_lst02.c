/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _lst02.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 00:30:47 by jrim              #+#    #+#             */
/*   Updated: 2022/07/17 13:36:02 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env		*init_envlst(char *key, char *val);
void		add_to_envlst(t_env **envlst, t_env *new);
t_toklst	*init_toklst(t_env *envlst);
void		add_to_toklst(t_toklst **toklst, t_toklst *new);

t_env		*init_envlst(char *key, char *val)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		err_alloc();
	new->key = key;
	new->val = val;
	new->next = NULL;
	return (new);
}

void		add_to_envlst(t_env **envlst, t_env *new)
{
	t_env *tmp;

	if (*envlst == NULL)
		(*envlst) = new;
	else
	{
		tmp = *envlst;
		while ((*envlst)->next)
			*envlst = (*envlst)->next;
		(*envlst)->next = new;
		*envlst = tmp;
	}
}


t_toklst	*init_toklst(t_env *envlst)
{
	t_toklst	*new;

	new = (t_toklst *)malloc(sizeof(t_toklst));
	if (!new)
		err_alloc();
	new->cmd = NULL;
	new->rdr_in = NULL;
	new->rdr_out = NULL;
	new->trash = NULL;
	new->envlst = envlst;
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
