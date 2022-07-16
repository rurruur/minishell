/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:12:05 by jrim              #+#    #+#             */
/*   Updated: 2022/07/16 15:12:00 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strndup(char *str, int n);
char	*msh_strjoin(char *s1, char *s2);

char	*ft_strndup(char *str, int n)
{
	int		idx;
	int		src_len;
	char	*dupstr;

	src_len = (int)ft_strlen(str);
	if (src_len < n)
		dupstr = (char *)malloc((src_len + 1) * sizeof(char));
	else
		dupstr = (char *)malloc((n + 1) * sizeof(char));
	if (!(dupstr))
		return (0);
	idx = 0;
	while (idx < src_len && idx < n)
	{
		dupstr[idx] = str[idx];
		idx++;
	}
	dupstr[idx] = '\0';
	return (dupstr);
}

char	*msh_strjoin(char *s1, char *s2)
{
	size_t	total_len;
	char	*new_str;

	if (!s1)
		return (NULL);
	if (!s2)
		return (s1);
	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	new_str = (char *)malloc(total_len * sizeof(char));
	if (!new_str)
		return (NULL);
	new_str[0] = '\0';
	if (total_len == 1)
		return (new_str);
	ft_strlcat(new_str, (char *)s1, ft_strlen(s1) + 1);
	ft_strlcat(new_str, (char *)s2, total_len);
	free(s1);
	free(s2);
	return (new_str);
}
