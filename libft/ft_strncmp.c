/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 21:25:41 by jrim              #+#    #+#             */
/*   Updated: 2021/11/14 21:25:48 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			idx;
	unsigned char	*s1_ptr;
	unsigned char	*s2_ptr;

	idx = 0;
	s1_ptr = (unsigned char *)s1;
	s2_ptr = (unsigned char *)s2;
	while ((s1[idx] != '\0' || s2[idx] != '\0') && idx < n)
	{
		if (s1_ptr[idx] != s2_ptr[idx])
			return (s1_ptr[idx] - s2_ptr[idx]);
		idx++;
	}
	return (0);
}
