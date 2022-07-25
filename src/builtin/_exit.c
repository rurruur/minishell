/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:36:39 by jrim              #+#    #+#             */
/*   Updated: 2022/07/25 10:25:50 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	msh_exit(t_token *argv, int type);
int		_exit_num_check(char *str);
void	_exit_err(int type, char *str);
int		_exit_status(char *str);

void	msh_exit(t_token *argv, int type)
{
	if (type != EXIT_PIPE)
		ft_putendl_fd("exit", STDOUT_FILENO);
	if (argv->next == NULL)
	{
		g_status = 0;
		exit(g_status);
	}
	else if (_exit_num_check(argv->next->str) != VALID)
		_exit_err(1, argv->next->str);
	else if (argv->next->next)
		_exit_err(2, argv->next->str);
	else
	{
		g_status = _exit_status(argv->next->str);
		exit(g_status);
	}
}

int	_exit_num_check(char *str)
{
	int	flag;
	int	len;

	flag = VALID;
	len = 0;
	if (*str == '-')
		str++;
	while (*str && flag == VALID)
	{
		if (!ft_isdigit(*str) || len > 19)
			flag = INVALID;
		str++;
		len++;
	}
	return (flag);
}

void	_exit_err(int type, char *str)
{
	ft_putstr_fd("gumshell: exit: ", STDERR_FILENO);
	if (type == 1)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		g_status = 255;
		exit(g_status);
	}
	else if (type == 2)
	{
		ft_putendl_fd(": too many arguments", STDERR_FILENO);
		g_status = 1;
	}
}

int	_exit_status(char *str)
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
		_exit_err(1, str);
	return ((sign * num) & 255);
}
