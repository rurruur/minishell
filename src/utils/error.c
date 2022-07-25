/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 15:11:42 by jrim              #+#    #+#             */
/*   Updated: 2022/07/25 12:35:32 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	err_parser(int err_type);
void	err_alloc(void);

void	err_parser(int err_type)
{
	ft_putstr_fd("gumshell: ", STDERR_FILENO);
	if (err_type == ERR_QUOTE)
		ft_putendl_fd("quote is not closed", STDERR_FILENO);
	else if (err_type == ERR_SYNTAX)
		ft_putendl_fd("syntax error", STDERR_FILENO);
	g_status = 258;
}

void	err_alloc(void)
{
	ft_putendl_fd("gumshell: Cannot allocate memory", STDERR_FILENO);
	g_status = 12;
	exit(g_status);
}
