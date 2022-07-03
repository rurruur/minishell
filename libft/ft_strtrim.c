/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 21:28:19 by jrim              #+#    #+#             */
/*   Updated: 2021/11/24 23:43:41 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	trimmed_len(char **ptr, char const *set)
{
	size_t	start;
	size_t	end;

	start = 0;
	if (ft_strlen(*ptr) == 0)
		return (0);
	end = ft_strlen(*ptr) - 1;
	while (ft_strchr(set, (*ptr)[start]) != 0 && (*ptr)[start])
		start++;
	if (start > end)
		return (0);
	while (ft_strchr(set, (*ptr)[end]) != 0)
		end--;
	(*ptr) += start;
	return (end - start + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	char	*new_str;
	size_t	new_len;
	size_t	idx;

	if (!s1 || !set)
		return (0);
	ptr = (char *)s1;
	new_len = trimmed_len(&ptr, set);
	new_str = (char *)malloc((new_len + 1) * sizeof(char));
	if (!(new_str))
		return (0);
	idx = 0;
	while (new_len--)
	{
		new_str[idx] = *ptr;
		idx++;
		ptr++;
	}
	new_str[idx] = '\0';
	return (new_str);
}
