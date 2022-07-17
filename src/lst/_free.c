/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _free.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 00:25:11 by jrim              #+#    #+#             */
/*   Updated: 2022/07/16 14:17:27 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_strarr(char **str);
void	free_strlst(t_token *strlst);
void	free_envlst(t_env *envlst);
void	free_toklst(t_toklst *toklst);

void	free_strarr(char **str)
{
	int	idx;

	idx = 0;
	if (!str)
		return ;
	while (str[idx])
	{
		free(str[idx]);
		idx++;
	}
	free(str);
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

void	free_envlst(t_env *envlst)
{
	t_env	*tmp;

	while (envlst)
	{
		tmp = envlst;
		envlst = envlst->next;
		free(tmp->key);
		free(tmp->val);
		tmp->key = NULL;
		tmp->val = NULL;
		tmp->next = NULL;
		free(tmp);
		tmp = NULL;
	}
}

void		free_toklst(t_toklst *toklst)
{
	t_toklst	*tmp;

	while (toklst)
	{
		tmp = toklst;
		toklst = toklst->next;
		free_strlst(tmp->cmd);
		free_strlst(tmp->infile);
		free_strlst(tmp->heredoc);
		free_strlst(tmp->rdr_out);
		free_strlst(tmp->trash);
		free(tmp);
		tmp = NULL;
	}
}