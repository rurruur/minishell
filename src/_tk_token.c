/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tk_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:27:38 by jrim              #+#    #+#             */
/*   Updated: 2022/07/06 18:13:58 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenizer(char **pretok, int *idx, t_toklst *new);
char	*quote_trim(char *str);

void	tokenizer(char **pretok, int *idx, t_toklst *new)
{
	t_token	*tmp;
	
	tmp = NULL;
	while (pretok[*idx] && pretok[*idx][0] != '|')
	{
		if (pretok[*idx][0] == '<')
		{
			tmp->str = ft_strdup(pretok[*idx + 1]);
			if (pretok[*idx][1] == '<')
				add_to_strlst(&(new->heredoc), tmp); 
			else
				add_to_strlst(&(new->infile), tmp); 
			(*idx)++;
		}
		else if (pretok[*idx][0] == '>')
		{
			tmp->str = ft_strdup(pretok[*idx + 1]);
			if (pretok[*idx][1] == '>')
				add_to_strlst(&(new->append), tmp); 
			else
				add_to_strlst(&(new->outfile), tmp); 
			(*idx)++;
		}
		else if (pretok[*idx][0] == '\'' || pretok[*idx][0] == '"')
		{
			tmp->str = quote_trim(pretok[*idx]);
			add_to_strlst(&(new->cmd), tmp); 
		}
		else
		{
			tmp->str = ft_strdup(pretok[*idx]);
			add_to_strlst(&(new->cmd), tmp); 
		}
		(*idx)++;
	}
	return (new);
}

char	*quote_trim(char *str)
{
	int 	len;
	char	*trimmed;

	len = (int)ft_strlen(str);
	trimmed = ft_strndup(str + 1, len - 2);
	return (trimmed);
}