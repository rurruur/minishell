/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 21:09:55 by jrim              #+#    #+#             */
/*   Updated: 2021/11/14 21:11:37 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst_ptr;
	unsigned char	*src_ptr;
	size_t			idx;

	if (len == 0 || dst == src)
		return (dst);
	dst_ptr = (unsigned char *)dst;
	src_ptr = (unsigned char *)src;
	idx = -1;
	if (dst < src)
		while (++idx < len)
			dst_ptr[idx] = src_ptr[idx];
	else
		while (++idx < len)
			dst_ptr[len - 1 - idx] = src_ptr[len - 1 - idx];
	return (dst);
}
