/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parser.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 00:15:11 by jrim              #+#    #+#             */
/*   Updated: 2022/07/06 19:44:20 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser_main(char *line, t_toklst *toklst);
int		check_quote(char *line);

void	parser_main(char *line, t_toklst *toklst)
{
	char		**pretok;
	int 		idx;
	t_toklst	*new;

	idx = 0;
	if (!check_quote(line))
		err_msg("quote");
	pretok = tok_split(line, ' ');
	// for (int i = 0; pretok[i]; i++)
	// 	printf("%s\n", pretok[i]);
	while (pretok[idx])
	{
		if (pretok[idx][0] != '|')
		{
			new = init_toklst();
			tokenizer(pretok, &idx, new);
			add_to_toklst(&toklst, new);
		}
		else
			idx++;
	}
	free_all(pretok);
	pretok = NULL;
	return;
}

int	check_quote(char *line)
{
	int	sq_flag;	// single quote flag
	int	dq_flag;	// double quote flag

	sq_flag = 1;
	dq_flag = 1;
	while (*line)
	{
		if (ft_strncmp(line, "\\'", 2) == 0 || ft_strncmp(line, "\\\"", 2) == 0)
		{
			line += 2;
			continue ;
		}
		if (dq_flag > 0 && *line == '\'')
			sq_flag = -sq_flag;
		if (sq_flag > 0 && *line == '"')
			dq_flag = -dq_flag;
		line++;
	}
	return (sq_flag + dq_flag > 0); // flag가 -1이면 quote가 안닫혔다는 의미
}