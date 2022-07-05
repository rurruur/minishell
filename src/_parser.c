/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parser.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 00:15:11 by jrim              #+#    #+#             */
/*   Updated: 2022/07/05 21:09:02 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser_main(char *line, t_toklst *toklst);
int		check_quote(char *line);

void	parser_main(char *line, t_toklst *toklst)
{
	char	**tokens;

	if (!check_quote(line))
		err_msg("quote");
	tokens = tok_split(line, ' ');
	for (int i = 0; tokens[i]; i++)
		printf("%s\n", tokens[i]);
	// while(*line)
	// {
	// 	// 일반 문자일 때 + escape 문자 error처리는 어떻게?
	// 	line++;
	// }
	free_all(tokens);
	tokens = NULL;
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