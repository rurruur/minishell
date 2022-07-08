/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tk_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:27:38 by jrim              #+#    #+#             */
/*   Updated: 2022/07/08 19:10:51 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenizer(t_token **pretok, t_toklst *new);
char	*trim_quote(char *str);

void	tokenizer(t_token **pretok, t_toklst *new)
{
	char	*tmp;
	
	tmp = NULL;
	while ((*pretok) && (*pretok)->str[0] != '|')
	{
		if ((*pretok)->str[0] == '<')
		{
			tmp = trim_quote((*pretok)->next->str);
			if ((*pretok)->str[1] == '<')
				add_to_strlst(&(new->heredoc), init_token(tmp)); 
			else
				add_to_strlst(&(new->infile), init_token(tmp)); 
			(*pretok) = (*pretok)->next;
		}
		else if ((*pretok)->str[0] == '>')
		{
			tmp = trim_quote((*pretok)->next->str);
			if ((*pretok)->str[1] == '>')
				add_to_strlst(&(new->append), init_token(tmp)); 
			else
				add_to_strlst(&(new->outfile), init_token(tmp)); 
			(*pretok) = (*pretok)->next;
		}
		else
		{
			tmp = trim_quote((*pretok)->str);
			add_to_strlst(&(new->cmd), init_token(tmp)); 
		}
		(*pretok) = (*pretok)->next;
	}
}

char	*trim_quote(char *str)
{
	int 	len;
	// int		quote;
	// int		dq;
	// int 	sq;
	char	*trimmed;

	len = (int)ft_strlen(str);
	// quote = cnt_quote(str);
	// if (quote == 0)
	trimmed = ft_strndup(str, len);
	// else
	// {
	// }
	return (trimmed);
}