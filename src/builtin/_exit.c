/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:36:39 by jrim              #+#    #+#             */
/*   Updated: 2022/07/23 16:42:26 by nakkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		msh_exit(t_token *argv, int type);
int		_exit_num_check(char *str);
void	_exit_err(int type, char *str, int exit_type);
int		_exit_status(char *str, int exit_type);

int	msh_exit(t_token *argv, int type)
{
	if (type != EXIT_PIPE)
		printf("exit\n");
	if (argv->next == NULL)
		g_status = 0;
	else if (_exit_num_check(argv->next->str) != 0)
		_exit_err(2, argv->next->str, type);
	else if (argv->next->next)
		_exit_err(1, argv->next->str, type);
	else
		g_status = _exit_status(argv->next->str, type);
	exit(g_status);
}

int	_exit_num_check(char *str)
{
	int	alpha;
	int	len;

	alpha = 0;
	len = 0;
	if (*str == '-')
		str++;
	while (*str && alpha == 0)
	{
		if (!ft_isdigit(*str))
			alpha = 1;
		str++;
		len++;
	}
	if (alpha == 1 && len > 19)
		alpha = -1;
	return (alpha);
}

void	_exit_err(int type, char *str, int exit_type)
{
	ft_putstr_fd("( ༎ຶД༎ຶ): exit: ", STDERR_FILENO);
	if (type == 1)
	{
		ft_putendl_fd(": too many arguments", STDERR_FILENO);
		if (exit_type == EXIT_PIPE)
			g_status = 1;
		else
			g_status = 257;
	}
	else if (type == 2)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		g_status = 255;
	}
}

int	_exit_status(char *str, int exit_type)
{
	unsigned long long	num;
	int					sign;

	num = 0;
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str != '\0' && ft_isdigit(*str) == 1)
	{
		num += (*str) - '0';
		if (ft_isdigit(*(str + 1)) == 1 && *(str + 1) != '\0')
			num *= 10;
		str++;
	}
	if ((sign == 1 && num > LLONG_MAX) || (sign == -1 && num - 1 > LLONG_MAX))
	{
		_exit_err(2, str, exit_type);
		return (255);
	}
	return ((sign * num) & 255);
}
