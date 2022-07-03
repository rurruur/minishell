/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 21:26:06 by jrim              #+#    #+#             */
/*   Updated: 2021/11/27 14:56:44 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	idx;
	size_t	needle_len;

	idx = 0;
	needle_len = ft_strlen(needle);
	if (haystack[0] == '\0' && needle[0] == '\0')
		return ((char *)haystack);
	while (*(haystack + idx) && idx + needle_len <= len)
	{
		if (ft_strncmp(haystack + idx, needle, needle_len) == 0)
			return ((char *)(haystack + idx));
		idx++;
	}
	return (0);
}
