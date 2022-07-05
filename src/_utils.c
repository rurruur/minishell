/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:12:05 by jrim              #+#    #+#             */
/*   Updated: 2022/07/05 17:19:48 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(char **str);
void	err_msg(char *str);
int		skip_space(char *str);
void	init_flag(t_flag *flag);
void	init_key(char *line, char *key);

void	free_all(char **str)
{
	int	idx;

	idx = 0;
	if (!str)
		return ;
	while (str[idx])
	{
		free(str[idx]);
		idx++;
	}
	free(str);
}

void	err_msg(char *str)
{
	printf("error: %s\n", str);
}

int		skip_space(char *str)
{
	int space;

	space = 0;
	while (*(str + space) == ' ')
		space++;
	return (space);
}

void	init_flag(t_flag *flag)
{
	flag->cmd = OFF;
	flag->quote = OFF;
	flag->rdr = OFF;
}

void	init_key(char *line, char *key)
{
	size_t	idx;
	size_t	len;
	
	idx = 0;
	line = ft_strlen(line);
	while (idx < len)
	{
		*(key + idx) = '-';
		idx++;
	}
	*(key + idx) = '\0';
}