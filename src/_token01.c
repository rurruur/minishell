/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _token01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:27:38 by jrim              #+#    #+#             */
/*   Updated: 2022/07/15 00:15:23 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		tokenizer(char *line, t_toklst *toklst);
void	check_env(t_token *pretok);
void	del_empty_tok(t_token *pretok);
void	tok_to_lst(t_token **pretok, t_toklst *new);

int	tokenizer(char *line, t_toklst *toklst)
{
	t_token		*pretok;
	t_toklst	*new;

	pretok = split_tok(line, " |<>");	// _token02.c
	// check_env(pretok);
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
	pretok = NULL;
	// system("leaks minishell > leaks_result; cat leaks_result | grep leaked && rm -rf leaks_result");
	return (1);
}

// void	check_env(t_token *pretok)
// {
// 	char *str;

// 	while (pretok)
// 	{
// 		str = pretok->str;
// 		while (str)
// 		{
// 			if ()

// 		}
// 		pretok = pretok->next;
// 	}
// }

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
	int		type;

	while ((*pretok) && (*pretok)->type != T_PIPE)
	{
		type = (*pretok)->type;
		if ((*pretok)->type > T_OFF)
		{
			lst_to_lst(pretok, &(new->trash));
			if (type == T_RDR_IN)
			{
				(*pretok)->type = T_RDR_IN;
				lst_to_lst(pretok, &(new->infile)); 
			}
			else if (type == T_RDR_HD)
			{
				(*pretok)->type = T_RDR_HD;
				lst_to_lst(pretok, &(new->heredoc)); 
			}
			else if (type == T_RDR_OUT)
			{
				(*pretok)->type = T_RDR_OUT;
				lst_to_lst(pretok, &(new->rdr_out)); 
			}
			else if (type == T_RDR_AP)
			{
				(*pretok)->type = T_RDR_AP;
				lst_to_lst(pretok, &(new->rdr_out)); 
			}
		}
		else
			lst_to_lst(pretok, &(new->cmd));
	}
}
