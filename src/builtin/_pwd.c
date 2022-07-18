/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _pwd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:36:50 by jrim              #+#    #+#             */
/*   Updated: 2022/07/17 21:33:11 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#define MAX_PATH_LEN 4096	// Linux maximum path length라고 검색한 결과

int	msh_pwd(t_token *argv)
{
	char	*pwd;
	char	buf[MAX_PATH_LEN];

	if (argv->next && (!ft_strcmp(argv->next->str, "-L")\
						|| !ft_strcmp(argv->next->str, "-P")))
		return (0);
	pwd = getcwd(buf, MAX_PATH_LEN);
	printf("%s\n", pwd);
	return (1);
}
