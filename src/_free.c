/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _free.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 00:25:11 by jrim              #+#    #+#             */
/*   Updated: 2022/07/14 00:27:02 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_strarr(char **str);
void	free_strlst(t_token **strlst);
void	free_toklst(t_toklst **toklst);

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