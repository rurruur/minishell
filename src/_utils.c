/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:12:05 by jrim              #+#    #+#             */
/*   Updated: 2022/07/05 00:26:34 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(char **str);
void	err_msg(char *str);
char	*ft_strndup(const char *s1, size_t n);

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

char	*ft_strndup(const char *s1, size_t n)
{
	unsigned int	idx;
	unsigned int	src_len;
	char			*dupstr;

	src_len = ft_strlen(s1);
	if (src_len < n)
		dupstr = (char *)malloc((src_len + 1) * sizeof(char));
	else
		dupstr = (char *)malloc((n + 1) * sizeof(char));
	if (!(dupstr))
		return (0);
	idx = 0;
	while (idx < src_len && idx < n)
	{
		dupstr[idx] = s1[idx];
		idx++;
	}
	dupstr[idx] = '\0';
	return (dupstr);
}