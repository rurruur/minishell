/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tk_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:27:38 by jrim              #+#    #+#             */
/*   Updated: 2022/07/06 20:15:58 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenizer(char **pretok, int *idx, t_toklst *new);
char	*quote_trim(char *str);

void	tokenizer(char **pretok, int *idx, t_toklst *new)
{
	char	*tmp;
	
	tmp = NULL;
	while (pretok[*idx] && pretok[*idx][0] != '|')
	{
		if (pretok[*idx][0] == '<')
		{
			tmp = quote_trim(pretok[*idx + 1]);
			if (pretok[*idx][1] == '<')
				add_to_strlst(&(new->heredoc), init_token(tmp)); 
			else
				add_to_strlst(&(new->infile), init_token(tmp)); 
			(*idx)++;
		}
		else if (pretok[*idx][0] == '>')
		{
			tmp = quote_trim(pretok[*idx + 1]);
			if (pretok[*idx][1] == '>')
				add_to_strlst(&(new->append), init_token(tmp)); 
			else
				add_to_strlst(&(new->outfile), init_token(tmp)); 
			(*idx)++;
		}
		else
		{
			tmp = quote_trim(pretok[*idx]);
			add_to_strlst(&(new->cmd), init_token(tmp)); 
		}
		(*idx)++;
	}
}

char	*quote_trim(char *str)
{
	int 	len;
	char	*trimmed;

	len = (int)ft_strlen(str);
	if (*str == '"' || *str == '\'')
		trimmed = ft_strndup(str + 1, len - 2);
	else
		trimmed = ft_strndup(str, len);
	return (trimmed);
}