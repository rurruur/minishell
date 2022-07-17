/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _pwd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:36:50 by jrim              #+#    #+#             */
/*   Updated: 2022/07/17 13:51:01 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#define MAX_PATH_LEN 4096	// Linux maximum path length라고 검색한 결과

int	msh_pwd(t_token *argv)
{
	char	*pwd;
	char	buf[MAX_PATH_LEN];

	if (argv->next && (!ft_strncmp(argv->next->str, "-L", ft_strlen(argv->next->str))\
						|| !ft_strncmp(argv->next->str, "-P", ft_strlen(argv->next->str))))
		return (0);
	pwd = getcwd(buf, MAX_PATH_LEN);
	printf("%s\n", pwd);
	return (1);
}