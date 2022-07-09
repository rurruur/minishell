/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _token01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:27:38 by jrim              #+#    #+#             */
/*   Updated: 2022/07/09 14:52:30 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenizer(char *line, t_toklst *toklst);
void	tok_to_lst(t_token **pretok, t_toklst *new);

void	tokenizer(char *line, t_toklst *toklst)
{
	t_token		*pretok;
	t_toklst	*new;

	pretok = split_tok(line, " |<>");
	// 여기서 전체적으로 quote 자르기
	while (pretok)
	{
		if (pretok->str[0] != '|')
		{
			new = init_toklst();
			tok_to_lst(&pretok, new);
			add_to_toklst(&toklst, new);
			if (!pretok)
				break;
		}
		pretok = pretok->next;
	}
	display_toklst(toklst);
	//free_all(pretok);
	//pretok = NULL;
	return;
}

void	tok_to_lst(t_token **pretok, t_toklst *new)
{
	char	*tmp;
	
	tmp = NULL;
	while ((*pretok) && (*pretok)->str[0] != '|')
	{
		if ((*pretok)->str[0] == '<' || (*pretok)->str[0] == '>')
		{
			tmp = trim_quote((*pretok)->next->str);
			if ((*pretok)->str[1] == '<')
				add_to_strlst(&(new->heredoc), init_token(tmp));
			else if ((*pretok)->str[1] == '>')
				add_to_strlst(&(new->append), init_token(tmp)); 
			else if ((*pretok)->str[0] == '<')
				add_to_strlst(&(new->infile), init_token(tmp)); 
			else if ((*pretok)->str[0] == '>')
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
