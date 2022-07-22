/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:36:39 by jrim              #+#    #+#             */
/*   Updated: 2022/07/22 17:24:57 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		msh_exit(t_token *argv, int type);
int		_exit_num_check(char *str);
void	_exit_err(int type, char *str);
int		_exit_status(char *str);

int		msh_exit(t_token *argv, int type)
{
	if (type != EXIT_PIPE)
		printf("exit\n");
	if (argv->next == NULL)
		g_status = 0;
	else if (_exit_num_check(argv->next->str) != 0)
		_exit_err(2, argv->next->str);
	else if (argv->next->next)
		_exit_err(1, argv->next->str);
	else
		g_status = _exit_status(argv->next->str);
	return (1);
}

int		_exit_num_check(char *str)
{
	int alpha;
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
	if (alpha == 1 && len > 19) // LLONG MAX
		alpha = -1;
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

// 9223372036854775807
int		_exit_status(char *str)
{
	unsigned long long	num;
	int					sign;
	int					exit_status;

	num = 0;
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (ft_isdigit(*str) == 1 && *str != '\0')
	{
		num += (*str) - '0';
		if (ft_isdigit(*(str + 1)) == 1 && *(str + 1) != '\0')
			num *= 10;
		str++;
	}
	if ((sign == 1 && num > LLONG_MAX) ||\
		(sign == -1 && num - 1 > LLONG_MAX))
	{
		_exit_err(2, str);
		exit_status = 255;
	}
	else
		exit_status = (sign * num) & 255;
	return (exit_status);
}
