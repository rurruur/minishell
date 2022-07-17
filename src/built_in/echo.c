/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:36:25 by jrim              #+#    #+#             */
/*   Updated: 2022/07/16 19:30:43 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	msh_echo(t_token *argv)
{
	int	n_opt;

	n_opt = 0;
	argv = argv->next;
	if (argv && !ft_strncmp(argv->str, "-n", ft_strlen(argv->str)))
	{
		n_opt = 1;
		argv = argv->next;
	}	
	while (argv)
	{
		printf("%s ", argv->str);
		argv = argv->next;
	}
	if (n_opt == 0)
		printf("\n");
	return (1);
}
