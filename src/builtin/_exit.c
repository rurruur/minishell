/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:36:39 by jrim              #+#    #+#             */
/*   Updated: 2022/07/21 22:53:40 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		msh_exit(t_token *argv, int type);
int		_exit_num_check(char *str);
void	_exit_err(int type, char *str);

int		msh_exit(t_token *argv, int type)
{
	int		exit_num;

	exit_num = 0;
	if (type != EXIT_PIPE)
		printf("exit\n");
	if (argv->next == NULL)
	{
		g_status = 0;
		return (1);
	}
	if (_exit_num_check(argv->next->str))
		_exit_err(2, argv->next->str);
	else if (argv->next->next)
		_exit_err(1, argv->next->str);
	else
	{
		// exit_num = ft_atoi(argv->next->str);
		// if (exit < 0)
		// 	exit_num += 256;
		// else
		// 	exit_num %= 256;
		(void)exit_num;
		// -255~256
		g_status = 0;
	}
	return (1);
}

int		_exit_num_check(char *str)
{
	int alpha;

	alpha = 0;
	if (*str == '-')
		str++;
	while (*str && alpha == 0)
	{
		if (!ft_isdigit(*str))
			alpha = 1;
		str++;
	}
	return (alpha);
}

void	_exit_err(int type, char *str)
{
	ft_putstr_fd("( ༎ຶД༎ຶ): exit: ", STDERR_FILENO);
	if (type == 1)
	{
		ft_putendl_fd(": too many arguments", STDERR_FILENO);
		g_status = 1;
	}
	else if (type == 2)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		g_status = 255;
	}
}
