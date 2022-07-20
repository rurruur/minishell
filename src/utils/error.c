/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 15:11:42 by jrim              #+#    #+#             */
/*   Updated: 2022/07/20 15:41:16 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	err_syntax(int err_type, char *str);
void	err_custom(int err_type, char *str);
void	err_alloc(void);

void	err_syntax(int err_type, char *str)
{
	printf("( ༎ຶД༎ຶ): ");
	if (err_type == 1)
		printf("syntax error near unexpected token `%s'\n", str);
	else if (err_type == 2)
		printf("syntax error near unexpected token `newline\'\n");
	g_status = 258;
}

void	err_custom(int err_type, char *str)
{
	printf("( ༎ຶД༎ຶ): ");
	if (err_type == 0) // quote error
		printf("quote is not closed\n");
	else if (err_type == 1) // 아직 쓰는 경우가 없...어
		printf("invalid character `%s' is found", str);
	g_status = 258;
}

void	err_alloc(void)
{
	printf("( ༎ຶД༎ຶ): ");
	printf("cannot allocate memory\n");
	g_status = 12;
	// 그러고 어쩔건데
}
