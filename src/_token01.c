/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _token01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:27:38 by jrim              #+#    #+#             */
/*   Updated: 2022/07/09 23:46:13 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenizer(char *line, t_toklst *toklst);
void	tok_to_lst(t_token **pretok, t_toklst *new);

void	tokenizer(char *line, t_toklst *toklst)
{
	t_token		*pretok;
	t_token		*tmp;
	t_toklst	*new;

	pretok = split_tok(line, " |<>");
	trim_pretok(pretok);
	// if (!check_pipe(pretok))
	// 	return ;
	// display_strlst(pretok);
	tmp = pretok;
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
	pretok = tmp;
	free_strlst(&pretok);
	display_toklst(toklst);
	return;
}

void	tok_to_lst(t_token **pretok, t_toklst *new)
{
	char	*tmp;

	while ((*pretok) && (*pretok)->str[0] != '|')
	{
		tmp = (*pretok)->str;
		if (tmp[0] == '<' || tmp[0] == '>')
		{
			(*pretok) = (*pretok)->next;
			if (tmp[1] == '<')
				add_to_strlst(&(new->heredoc), init_strlst((*pretok)->str)); 
			else if (tmp[1] == '>')
				add_to_strlst(&(new->append), init_strlst((*pretok)->str)); 
			else if (tmp[0] == '<')
				add_to_strlst(&(new->infile), init_strlst((*pretok)->str)); 
			else if (tmp[0] == '>')
				add_to_strlst(&(new->outfile), init_strlst((*pretok)->str)); 
		}
		else
		{
			add_to_strlst(&(new->cmd), init_strlst((*pretok)->str));
			(*pretok) = (*pretok)->next;
		}
	}
}
