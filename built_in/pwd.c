/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:36:50 by jrim              #+#    #+#             */
/*   Updated: 2022/07/13 18:44:17 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

#define MAX_PATH_LEN 4096	// Linux maximum path length라고 검색한 결과

void	pwd(void)
{
	char	*pwd;
	char	buf[MAX_PATH_LEN];

	pwd = getcwd(buf, MAX_PATH_LEN);
	if (!pwd)
	{
		printf("error?\n");
		return ;
	}
	printf("%s\n", pwd);
}