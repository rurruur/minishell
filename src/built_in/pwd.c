/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:36:50 by jrim              #+#    #+#             */
/*   Updated: 2022/07/16 17:25:12 by nakkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#define MAX_PATH_LEN 4096	// Linux maximum path length라고 검색한 결과

void	msh_pwd(void)
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