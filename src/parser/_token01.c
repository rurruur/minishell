/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _token01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:27:38 by jrim              #+#    #+#             */
/*   Updated: 2022/07/17 02:03:11 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_toklst	*tokenizer(char *line, t_toklst *toklst, t_env *envlst);
int			pretoknizer(char *line, t_token **pretok, t_env *envlst);
void		tok_to_lst(t_token **pretok, t_toklst *new);

t_toklst	*tokenizer(char *line, t_toklst *toklst, t_env *envlst)
{
	t_token		*pretok;
	t_toklst	*new;

	if (!pretoknizer(line, &pretok, envlst))
		return (NULL);
	while (pretok)
	{
		if (pretok->type != T_PIPE)
		{
			new = init_toklst(envlst);
			tok_to_lst(&pretok, new);
			add_to_toklst(&toklst, new);
		}
		if (pretok && pretok->next)
			pretok = pretok->next;
	}
	pretok = NULL;
	return (toklst);
}

int		pretoknizer(char *line, t_token **pretok, t_env *envlst)
{
	if (check_whitespace(line) || !check_quote(line))
		return (0);	// escape 처리는?
	(*pretok) = split_tok(line, " |<>");
	env_to_str(*pretok, envlst);
	trim_pretok(*pretok);
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
