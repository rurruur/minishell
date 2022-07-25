/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:07:02 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/25 10:49:50 by nakkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(char *err_msg)
{
	ft_putstr_fd("gumshell: ", STDERR_FILENO);
	ft_putstr_fd(err_msg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (errno <= MAX_ERRNO)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		exit(errno);
	}
	else if (errno == CMD_NOT_FOUND)
		ft_putendl_fd("command not found", STDERR_FILENO);
	else if (errno == IS_DIR)
		ft_putendl_fd("is a directory", STDERR_FILENO);
	else if (errno == NO_EXIST)
		ft_putendl_fd("No such file or directory", STDERR_FILENO);
	exit(errno - MAX_ERRNO);
}

void	ft_file_error(char *err_msg)
{
	g_status = 1;
	ft_putstr_fd("gumshell: ", STDERR_FILENO);
	ft_putstr_fd(err_msg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (errno <= MAX_ERRNO)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return ;
	}
	else if (errno == CMD_NOT_FOUND)
		ft_putendl_fd("command not found", STDERR_FILENO);
	else if (errno == IS_DIR)
		ft_putendl_fd("Is a directory", STDERR_FILENO);
	else if (errno == NO_EXIST)
		ft_putendl_fd("No such file or directory", STDERR_FILENO);
}
