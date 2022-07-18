/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:27:38 by jrim              #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/07/17 21:29:46 by jrim             ###   ########.fr       */
=======
/*   Updated: 2022/07/17 17:24:07 by nakkim           ###   ########.fr       */
>>>>>>> 347fb381f957dbffd1947b04fe484d2097af99e5
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
<<<<<<< HEAD
=======
	// display_strlst(pretok);
>>>>>>> 347fb381f957dbffd1947b04fe484d2097af99e5
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

int	pretoknizer(char *line, t_token **pretok, t_env *envlst)
{
	if (check_whitespace(line) || !check_quote(line))
		return (0);
	(*pretok) = split_tok(line, " |<>");
	display_strlst(*pretok);
	env_to_str(*pretok, envlst);
	trim_pretok(*pretok);
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
			del_from_strlst(pretok);
			(*pretok)->type = type;
			if (type == T_RDR_IN || type == T_RDR_HD)
				lst_to_lst(pretok, &(new->rdr_in));
			else if (type == T_RDR_OUT || type == T_RDR_AP)
				lst_to_lst(pretok, &(new->rdr_out));
		}
		else
			lst_to_lst(pretok, &(new->cmd));
	}
}
