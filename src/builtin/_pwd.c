/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _pwd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:36:50 by jrim              #+#    #+#             */
/*   Updated: 2022/07/24 15:54:49 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	msh_pwd(void)
{
	char	*pwd;

	pwd = getcwd(0, MAX_PATH_LEN);
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
}
