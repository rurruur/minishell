/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _echo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:36:25 by jrim              #+#    #+#             */
/*   Updated: 2022/07/24 17:15:34 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	msh_echo(t_token *argv);
int		_echo_opt(char *str);

void	msh_echo(t_token *argv)
{
	int	n_opt;

	n_opt = 0;
	argv = argv->next;
	while (argv)
	{
		if (_echo_opt(argv->str))
			n_opt = 1;
		else
			break ;
		argv = argv->next;
	}
	while (argv)
	{
		ft_putstr_fd(argv->str, STDOUT_FILENO);
		argv = argv->next;
		if (argv)
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (n_opt == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
}

int	_echo_opt(char *str)
{
	if (ft_strncmp(str, "-n", 2))
		return (0);
	else
	{
		str += 2;
		while (*str)
		{
			if (*str != 'n')
				return (0);
			str++;
		}
		return (1);
	}
}
