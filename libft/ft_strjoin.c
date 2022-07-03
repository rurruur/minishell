/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 21:20:33 by jrim              #+#    #+#             */
/*   Updated: 2022/04/26 19:29:35 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_len;
	char	*new_str;

	if (!s1)
		return (0);
	if (!s2)
		return ((char *)s1);
	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	new_str = (char *)malloc(total_len * sizeof(char));
	if (!new_str)
		return (0);
	new_str[0] = '\0';
	if (total_len == 1)
		return (new_str);
	ft_strlcat(new_str, (char *)s1, ft_strlen(s1) + 1);
	ft_strlcat(new_str, (char *)s2, total_len);
	return (new_str);
}
