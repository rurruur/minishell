/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parser.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 00:15:11 by jrim              #+#    #+#             */
/*   Updated: 2022/07/05 01:57:40 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser_main(char *line, t_toklst *toklst);
int		parser_quote(char *line, t_token *token, int *cmd_flag);
int		parser_redir(char *line, t_token *token);
int		parser_cmd(char *line, t_token *token, int *cmd_flag);

void	parser_main(char *line, t_toklst *toklst)
{
	t_tokcnt	*checker;
	t_token		*token;
	int			cmd_flag; // 1일때는 cmd, 0일 때는 param 취급

	token = NULL; // 나중에 지워라
	checker = (t_tokcnt *)malloc(sizeof(t_tokcnt));
	if (!checker)
		err_msg("allocation");
	checker_main(line, checker);
	//checker가 준 결과에 맞춰서 t_token에서의 할당이 필요하다.
	//checker에서 invalid pipe나 quote pair error 등은 미리 처리하도록
	cmd_flag = 0; // 나중에 지워라
	while(*line)
	{
		cmd_flag = 1;
		// if (*line == ' ')
		// 	line++;
		// else if (ft_strchr(QUOTE, *line))
		// 	line += parser_quote(line, token, &cmd_flag);
		// else if (ft_strchr("<>", *line))
		// 	line += parser_redir(line, token);
		// else if (*line == '|')
		// {
		// 	add_token(toklst, token);
		// 	line++;
		// }
		// else // 일반 문자일 때 + escape 문자 error처리는 어떻게?
		// 	line += parser_cmd(line, token, &cmd_flag);
	}
	if (token && toklst && cmd_flag)
		printf("");
	printf("parser in\n");
}
