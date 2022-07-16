/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:36:25 by jrim              #+#    #+#             */
/*   Updated: 2022/07/16 15:28:42 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

// int	check_n_opt(t_token *argv);

void	msh_echo(t_token *argv)
{
	if (argv)
		printf("echo 아직 안만들었단다\n");

	// int	idx;
	// int	n_opt;

	// idx = 1;
	// n_opt = 0;
	// // -n option check를 먼저 해야할까?
	// if (argv[idx])	// list->size로 할까?
	// {
	// 	// quote에 관한 처리들은 src/_token03.c에 있는 함수들 이용하면 될 듯
	// 	if (n_opt == 1)
	// 		printf("\n");
	// }
}

// int	check_n_opt(t_token *argv)
// {
	
// }