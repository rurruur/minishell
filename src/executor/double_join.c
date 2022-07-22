/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 00:09:42 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/23 00:11:24 by nakkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*double_strjoin(char *start, char *middle, char *end)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(start, middle);
	if (!tmp)
		ft_error("malloc");
	result = ft_strjoin(tmp, end);
	if (!result)
		ft_error("malloc");
	free(tmp);
	return (result);
}
