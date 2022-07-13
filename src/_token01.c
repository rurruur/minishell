/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _token01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:27:38 by jrim              #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/07/11 23:47:35 by jrim             ###   ########.fr       */
=======
/*   Updated: 2022/07/13 18:28:26 by jrim             ###   ########.fr       */
>>>>>>> 2d91312d505f7e636afcb5272ec59583eb06c596
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		tokenizer(char *line, t_toklst *toklst);
void	del_empty_tok(t_token *pretok);
void	tok_to_lst(t_token **pretok, t_toklst *new);

int	tokenizer(char *line, t_toklst *toklst)
{
	t_token		*pretok;
	t_toklst	*new;

	pretok = split_tok(line, " |<>");	// _token02.c
	trim_pretok(pretok);				// _token03.c
	del_empty_tok(pretok);
	if (!pretok || !check_pretok(pretok))
		return (0);
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
	// free_strlst(&pretok);
	pretok = NULL;
	return (1);
}

void	del_empty_tok(t_token *pretok)
{
	while (pretok)
	{
		if (pretok->next && pretok->next->str[0] == '\0')
			del_from_strlst(&pretok);
		else
			pretok = pretok->next;
	}
}

void	tok_to_lst(t_token **pretok, t_toklst *new)
{
	int	type;

	while ((*pretok) && (*pretok)->type != T_PIPE)
	{
		type = (*pretok)->type;
		if ((*pretok)->type > T_OFF)
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
