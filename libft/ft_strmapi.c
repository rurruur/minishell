/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 21:24:15 by jrim              #+#    #+#             */
/*   Updated: 2021/11/24 23:42:23 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			s_len;
	unsigned int	idx;
	char			*new_str;

	if (!s || !f)
		return (0);
	s_len = ft_strlen(s);
	new_str = (char *)malloc((s_len + 1) * sizeof(char));
	if (!new_str)
		return (0);
	idx = 0;
	while (s[idx] != '\0')
	{
		new_str[idx] = f(idx, s[idx]);
		idx++;
	}
	new_str[idx] = '\0';
	return (new_str);
}
