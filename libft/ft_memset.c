/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 21:12:52 by jrim              #+#    #+#             */
/*   Updated: 2021/11/14 21:13:16 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*b_ptr;
	size_t			idx;

	b_ptr = (unsigned char *)b;
	idx = 0;
	while (idx < len)
		b_ptr[idx++] = (unsigned char)c;
	return (b);
}
