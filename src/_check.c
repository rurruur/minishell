/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _check.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 17:01:52 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/04 00:06:22 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote(char *line);
int	check_pipe(char **cmd_token);
int	check_RDR(char *line);

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
			continue;
		}
		if (dq_flag > 0 && *line == '\'')
			sq_flag = -sq_flag;
		if (sq_flag > 0 && *line == '"')
			dq_flag = -dq_flag;
		line++;
	}
	return (sq_flag + dq_flag > 0); // flag가 -1이면 quote가 안닫혔다는 의미
}

int	check_pipe(char **cmd_token)
{
	int	flag;
	int	idx;

	flag = 1;
	idx = 1;
	if (cmd_token[0][0] == '|')
		flag = 0;
	while (cmd_token[idx])
	{
		// 'cat test | '처럼 pipe 뒤에 아무것도 없는 경우 새로운 프롬프트가 명령을 마저 받아와야한다....
		// wrong_cmd | cmd : 뒤에만 실행해야함
		// cmd | wrong_cmd : command not found
		// | cmd : parse error near `|'
		// | : parse error near `|'
		if (cmd_token[idx][0] == '|' && !cmd_token[idx + 1]) // 수정하거나 조건 추가해야함
			printf("need more!\n");
		idx++;
	}
	return (flag);
}