/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 15:11:42 by jrim              #+#    #+#             */
/*   Updated: 2022/07/17 13:52:25 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_errmsg(int err_type,char *str);
void	err_syntax(int err_type, char *str);
void	err_custom(int err_type, char *str);
void	err_alloc(void);

void	print_errmsg(int err_type, char *str)
{
	if (err_type)
		printf("error: %s\n", str);
		
	// printf("minishell: %s: command not found\n");
	// printf("minishell: %s: too many arguments\n");
	// printf("minishell: %s: No such file or directory\n");
	// printf("minishell: %s: %s: numeric argument required\n");
	// // exprot error
	// // unset error
}

void	err_syntax(int err_type, char *str)
{
	if (err_type == 1)
		printf("minishell: syntax error near unexpected token `%s'\n", str);
	else if (err_type == 2)
		printf("minishell: syntax error near unexpected token `newline\'\n");
}

void	err_custom(int err_type, char *str)
{
	if (err_type == 0) // quote error
		printf("minishell: quote is not closed\n");
	else if (err_type == 1)
		printf("minishell: invalid character `%s' is found", str);
}

void	err_alloc(void)
{
	printf("minishell : cannot allocate memory\n");
	// 그러고 어쩔건데
}