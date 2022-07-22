/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 15:11:42 by jrim              #+#    #+#             */
/*   Updated: 2022/07/23 00:49:15 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	err_parser(int err_type);
void	err_alloc(void);

void	err_parser(int err_type)
{
	printf("( ༎ຶД༎ຶ): ");
	if (err_type == ERR_QUOTE)
		printf("quote is not closed\n");
	else if (err_type == ERR_SYNTAX)
		printf("syntax error\n");
	g_status = 258;
}

void	err_alloc(void)
{
	printf("( ༎ຶД༎ຶ): cannot allocate memory\n");
	g_status = 12;
	exit(g_status);
}
