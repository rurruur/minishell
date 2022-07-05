/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parser.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 00:15:11 by jrim              #+#    #+#             */
/*   Updated: 2022/07/05 17:59:10 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser_main(char *line, t_toklst *toklst);

void	parser_main(char *line, t_toklst *toklst)
{
	t_token		*token;
	t_flag		*flag;
	char		*key;

	token = NULL; // 나중에 지워라
	key = (char *)malloc((ft_strlen(line) + 1) * sizeof(char));
	if (!key)
		err_msg("key allocation");
	checker_main(line, key);
	flag = (t_flag *)malloc(sizeof(t_flag));
	if (!flag)
		err_msg("flag allocation");
	init_flag(flag);
	while(*line)
	{
		line += skip_space(key);
		key += skip_space(key);
		if (flag->rdr == OFF && ft_strchr(RDR, *key))
		{
			if (*key == '<')
				flag->rdr = IN;	
			else if (*key == '>')
				flag->rdr = OUT;
			else if (ft_strncmp(key, "<<", 2))
				flag->rdr = HD;
			else if (ft_strncmp(key, ">>", 2))
				flag->rdr = AP;		
		}
		else if (flag->quote == OFF && ft_strchr(QUOTE, *key))
			flag->quote = ON;
		else if (flag->quote == ON)	//뭐가 나오든 다 str 처리
		{
			if (flag->rdr != OFF)
			{
				//담아주는 데에 보내야함 rdr 매크로 맞춰서
				flag->rdr = OFF;
			}
			else if (flag->cmd == OFF)
			{
				flag->cmd = ON;
				//cmd에 담아주기
			}
			else if (flag->cmd == ON)
			{
				//param에 담아주기
			}
		}
		else if (flag->quote == OFF && *line == '|')
			add_token(toklst, token);
		// 일반 문자일 때 + escape 문자 error처리는 어떻게?
		line++;
		key++;
	}
}
