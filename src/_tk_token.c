/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tk_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:27:38 by jrim              #+#    #+#             */
/*   Updated: 2022/07/08 16:00:27 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenizer(t_token **pretok, t_toklst *new);
char	*quote_trim(char *str);

void	tokenizer(t_token **pretok, t_toklst *new)
{
	char	*tmp;
	
	tmp = NULL;
	while ((*pretok) && (*pretok)->str[0] != '|')
	{
		// display_strlst(*pretok);
		if ((*pretok)->str[0] == '<')
		{
			// printf("< in\n");
			tmp = quote_trim((*pretok)->next->str);
			// printf("tmp1 : %s\n", tmp);
			if ((*pretok)->str[1] == '<')
				add_to_strlst(&(new->heredoc), init_token(tmp)); 
			else
				add_to_strlst(&(new->infile), init_token(tmp)); 
			(*pretok) = (*pretok)->next;
		}
		else if ((*pretok)->str[0] == '>')
		{
			// printf("> in\n");
			tmp = quote_trim((*pretok)->next->str);
			// printf("tmp2 : %s\n", tmp);
			if ((*pretok)->str[1] == '>')
				add_to_strlst(&(new->append), init_token(tmp)); 
			else
				add_to_strlst(&(new->outfile), init_token(tmp)); 
			(*pretok) = (*pretok)->next;
		}
		else
		{
			// printf("else in\n");
			tmp = quote_trim((*pretok)->str);
			// printf("tmp3 : %s\n", tmp);
			add_to_strlst(&(new->cmd), init_token(tmp)); 
			// display_strlst(new->cmd);
			// printf("cmd : %s\n", new->cmd->str);
		}
		(*pretok) = (*pretok)->next;
	}
	// display_strlst(*pretok);
}

char	*quote_trim(char *str)
{
	int 	len;
	char	*trimmed;

	len = (int)ft_strlen(str);
	// if ((*str == '"' || *str == '\'') && str[len - 1] == *str)
	// 	trimmed = ft_strndup(str + 1, len - 2);
	// else
		trimmed = ft_strndup(str, len);
	return (trimmed);
}