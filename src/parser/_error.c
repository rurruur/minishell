/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _error.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 15:11:42 by jrim              #+#    #+#             */
/*   Updated: 2022/07/16 15:22:31 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_errmsg(char *str);

void	print_errmsg(char *str)
{
	printf("error: %s\n", str);

	// printf("minishell: %s: command not found\n");
	// printf("minishell: %s: too many arguments\n");
	// printf("minishell: %s: No such file or directory\n");
	// printf("minishell: %s: %s: numeric argument required\n");
	// // exprot error
	// // unset error

	// printf("minishell: syntax error near unexpected token `%s'\n");
	// printf("minishell: syntax error near unexpected token `%s\'\n");
	// printf("minishell: syntax error near unexpected token `newline\'\n");
}