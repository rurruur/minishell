/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _token01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:27:38 by jrim              #+#    #+#             */
/*   Updated: 2022/07/10 22:47:55 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenizer(char *line, t_toklst *toklst);
void	tok_to_lst(t_token **pretok, t_toklst *new);

void	tokenizer(char *line, t_toklst *toklst)
{
	t_token		*pretok;
	// t_token		*tmp;
	t_toklst	*new;

	pretok = split_tok(line, " |<>");
	trim_pretok(pretok);
	if (!check_pretok(pretok))
		return ;
	// tmp = pretok;
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
	// pretok = tmp;
	// free_strlst(&pretok);
	return;
}

void	tok_to_lst(t_token **pretok, t_toklst *new)
{
	int	type;

	while ((*pretok) && (*pretok)->str[0] != '|')
	{
		type = (*pretok)->type;
		if (type != OFF)
		{
			lst_to_lst(pretok, &(new->rdr));
			if (type == RDR_IN)
				lst_to_lst(pretok, &(new->infile)); 
			else if (type == RDR_HD)
				lst_to_lst(pretok, &(new->heredoc)); 
			else if (type == RDR_OUT)
				lst_to_lst(pretok, &(new->outfile)); 
			else if (type == RDR_AP)
				lst_to_lst(pretok, &(new->append)); 
		}
		else
			lst_to_lst(pretok, &(new->cmd));
	}
}
