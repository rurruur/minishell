/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:36:39 by jrim              #+#    #+#             */
/*   Updated: 2022/07/20 14:17:51 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// $? : return value of previous command
int		msh_exit(t_token *argv);
void	_exit_err(int type, char *str);

int	msh_exit(t_token *argv)
{
	int	 	alpha;
	char	*str;

	alpha = 0;
	printf("exit\n");
	if (argv->next == NULL)
		exit (0);
	str = argv->next->str;
	while (*str)
	{
		if (ft_isalpha(*str) == 1)
		{
			alpha = 1;
			break ;
		}
		str++;
	}
	if (alpha == 1)
		_exit_err(2, str);
	else if (argv->next->next)
		_exit_err(1, str);
	else
		exit (ft_atoi(argv->next->str));
	return (1);
}

void	_exit_err(int type, char *str)
{
	ft_putstr_fd("( ༎ຶД༎ຶ): exit: ", STDERR_FILENO);
	if (type == 1)
		ft_putendl_fd(": too many arguments", STDERR_FILENO);
	else if (type == 2)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit (1);
	}
}