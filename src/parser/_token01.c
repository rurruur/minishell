/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _token.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:27:38 by jrim              #+#    #+#             */
/*   Updated: 2022/07/15 14:41:10 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		tokenizer(char *line, t_toklst *toklst);
int		pretoknizer(char *line, t_token **pretok);
void	tok_to_lst(t_token **pretok, t_toklst *new);

int	tokenizer(char *line, t_toklst *toklst)
{
	t_token		*pretok;
	t_toklst	*new;

	if (!pretoknizer(line, &pretok))
		return (0);
	while (pretok)
	{
		if (pretok->type != T_PIPE)
		{
			new = init_toklst();
			tok_to_lst(&pretok, new);
			add_to_toklst(&toklst, new);
		}
		if (pretok && pretok->next)
			pretok = pretok->next;
	}
	pretok = NULL;
	// system("leaks minishell > leaks_result; cat leaks_result | grep leaked && rm -rf leaks_result");
	return (1);
}

int		pretoknizer(char *line, t_token **pretok)
{
	if (check_whitespace(line) || !check_quote(line))	// 짝 안맞는 따옴표는 미리 거르기
		return (0);	// escape 처리는?
	(*pretok) = split_tok(line, " |<>");	// _token02.c
	// check_env(*pretok);
	trim_pretok(*pretok);				// _token03.c
	check_empty(*pretok);
	if (!(*pretok) || !check_pretok(*pretok))
		return (0);
	return (1);
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
			(*pretok)->type = type;
			if (type == T_RDR_IN)
				lst_to_lst(pretok, &(new->infile)); 
			else if (type == T_RDR_HD)
				lst_to_lst(pretok, &(new->heredoc)); 
			else if (type == T_RDR_OUT || type == T_RDR_AP)
				lst_to_lst(pretok, &(new->rdr_out)); 
		}
		else
			lst_to_lst(pretok, &(new->cmd));
	}
}
