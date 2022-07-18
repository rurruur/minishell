/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:07:02 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/18 17:15:57 by nakkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(char *err_msg)
{
	ft_putstr_fd("( ༎ຶД༎ຶ): ", STDERR_FILENO);
	ft_putstr_fd(err_msg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (errno > 0)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		exit(errno);
	}
	else if (errno == CMD_NOT_FOUND)
	{
		ft_putendl_fd("command not found", STDERR_FILENO);
		exit(127);
	}
	else if (errno == IS_DIR)
	{
		ft_putendl_fd("Is a directory", STDERR_FILENO);
		exit(126);
	}
}