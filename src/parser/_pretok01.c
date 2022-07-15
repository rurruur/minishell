/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _pretok01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 14:28:41 by jrim              #+#    #+#             */
/*   Updated: 2022/07/15 14:29:30 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		pretoknizer(char *line, t_token **pretok);
void	check_env(t_token *pretok);
void	del_empty_tok(t_token *pretok);

int		pretoknizer(char *line, t_token **pretok)
{
	if (check_whitespace(line) || !check_quote(line))	// 짝 안맞는 따옴표는 미리 거르기
		return (0);	// escape 처리는?
	(*pretok) = split_tok(line, " |<>");	// _token02.c
	// check_env(*pretok);
	trim_pretok(*pretok);				// _token03.c
	del_empty_tok(*pretok);
	if (!(*pretok) || !check_pretok(*pretok))
		return (0);
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