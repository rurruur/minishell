/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 15:15:25 by jrim              #+#    #+#             */
/*   Updated: 2022/05/10 16:52:09 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strjoin(char *s1, char *s2)
{
	size_t	total_len;
	char	*new_str;

	if (!(s2))
		return ((char *)s1);
	total_len = gnl_strlen(s1) + gnl_strlen(s2) + 1;
	new_str = (char *)malloc(total_len * sizeof(char));
	if (!new_str)
		return (0);
	new_str[0] = '\0';
	if (total_len == 1)
		return (new_str);
	gnl_strlcat(new_str, (char *)s1, gnl_strlen(s1) + 1);
	gnl_strlcat(new_str, (char *)s2, total_len);
	free(s1);
	return (new_str);
}

size_t	gnl_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

size_t	gnl_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	idx;

	dst_len = gnl_strlen(dst);
	src_len = gnl_strlen(src);
	idx = 0;
	if (dst_len + 1 > dstsize)
		return (src_len + dstsize);
	while (src != 0 && src[idx] != '\0' && dst_len + idx + 1 < dstsize)
	{
		dst[dst_len + idx] = src[idx];
		idx++;
	}
	dst[dst_len + idx] = '\0';
	return (dst_len + src_len);
}

char	*gnl_strchr(const char *s, int c)
{
	size_t	idx;
	size_t	s_len;
	char	*ptr;

	if (!s)
		return (0);
	idx = 0;
	s_len = gnl_strlen(s) + 1;
	ptr = (char *)s;
	while (idx < s_len)
	{
		if (*ptr == (char)c)
			return (ptr);
		idx++;
		ptr++;
	}
	return (0);
}

char	*gnl_strndup(const char *s1, size_t n)
{
	unsigned int	idx;
	unsigned int	src_len;
	char			*dupstr;

	src_len = gnl_strlen(s1);
	if (src_len < n)
		dupstr = (char *)malloc((src_len + 1) * sizeof(char));
	else
		dupstr = (char *)malloc((n + 1) * sizeof(char));
	if (!(dupstr))
		return (0);
	idx = 0;
	while (idx < src_len && idx < n)
	{
		dupstr[idx] = s1[idx];
		idx++;
	}
	dupstr[idx] = '\0';
	return (dupstr);
}
