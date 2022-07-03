/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 21:19:39 by jrim              #+#    #+#             */
/*   Updated: 2021/11/24 23:41:18 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	idx;

	if (!s || !f)
		return ;
	idx = 0;
	while (s[idx] != '\0')
	{
		f(idx, &s[idx]);
		idx++;
	}
}
