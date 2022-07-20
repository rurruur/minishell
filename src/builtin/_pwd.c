/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _pwd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:36:50 by jrim              #+#    #+#             */
/*   Updated: 2022/07/20 20:04:14 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	msh_pwd(t_token *argv)
{
	char	*pwd;

	if (argv->next && (!ft_strcmp(argv->next->str, "-L") \
						|| !ft_strcmp(argv->next->str, "-P")))
		return (0);
	pwd = getcwd(0, MAX_PATH_LEN);
	printf("%s\n", pwd);
	free(pwd);
	return (1);
}
