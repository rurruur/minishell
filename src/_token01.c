/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _token01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:27:38 by jrim              #+#    #+#             */
/*   Updated: 2022/07/11 17:54:42 by jrim             ###   ########.fr       */
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

	pretok = NULL;
	pretok = split_tok(line, " |<>");
	display_strlst(pretok);
	trim_pretok(pretok);
	display_strlst(pretok);
	if (!pretok)
		return ;
	if (!check_pretok(pretok))
		return ;
	// tmp = pretok;
	while (pretok)
	{
		if (pretok->type != T_PIPE)
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

	while ((*pretok) && (*pretok)->type != T_PIPE)
	{
		type = (*pretok)->type;
		if (type > T_OFF)
		{
			lst_to_lst(pretok, &(new->rdr));
			if (type == T_RDR_IN)
				lst_to_lst(pretok, &(new->infile)); 
			else if (type == T_RDR_HD)
				lst_to_lst(pretok, &(new->heredoc)); 
			else if (type == T_RDR_OUT)
				lst_to_lst(pretok, &(new->outfile)); 
			else if (type == T_RDR_AP)
				lst_to_lst(pretok, &(new->append)); 
		}
		else
			lst_to_lst(pretok, &(new->cmd));
	}
}
