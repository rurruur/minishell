/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parser.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 00:15:11 by jrim              #+#    #+#             */
/*   Updated: 2022/07/05 22:28:29 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser_main(char *line, t_toknd *toklst);
int		check_quote(char *line);

void	parser_main(char *line, t_toknd *toklst)
{
	char	**pretok;
	int 	idx;
	t_token *content;

	idx = 0;
	if (!check_quote(line))
		err_msg("quote");
	pretok = tok_split(line, ' ');
	for (int i = 0; pretok[i]; i++)
		printf("%s\n", pretok[i]);
	content = NULL;
	while (pretok[idx])
	{
		if (pretok[idx][0] != '|')
			content = trim_pretok(pretok, &idx, toklst);
		add_token(&toklst, init_token(content));
		idx++;
	}
	free_all(pretok);
	pretok = NULL;
	if (toklst)
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