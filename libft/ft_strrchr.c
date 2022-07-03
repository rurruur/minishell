/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 21:26:59 by jrim              #+#    #+#             */
/*   Updated: 2021/11/14 21:28:05 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	idx;
	size_t	s_len;
	char	*ptr;

	idx = 0;
	s_len = ft_strlen(s) + 1;
	ptr = 0;
	while (idx < s_len)
	{
		if (s[idx] == (char)c)
			ptr = (char *)s + idx;
		idx++;
	}
	return (ptr);
}
