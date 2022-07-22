/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:12:05 by jrim              #+#    #+#             */
/*   Updated: 2022/07/23 01:24:00 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_strcmp(const char *s1, const char *s2);
char	*msh_strdup(char *s1);
char	*msh_strndup(char *str, int n);
char	*msh_strjoin(char *s1, char *s2);

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			idx;
	unsigned char	*s1_ptr;
	unsigned char	*s2_ptr;

	idx = 0;
	s1_ptr = (unsigned char *)s1;
	s2_ptr = (unsigned char *)s2;
	if (s2 == NULL && ft_strlen(s1) == 0)
		return (0);
	while ((s1[idx] != '\0' || s2[idx] != '\0'))
	{
		if (s1_ptr[idx] != s2_ptr[idx])
			return (s1_ptr[idx] - s2_ptr[idx]);
		idx++;
	}
	return (0);
}

char	*msh_strdup(char *s1)
{
	unsigned int	idx;
	unsigned int	src_len;
	char			*dupstr;

	src_len = ft_strlen(s1);
	dupstr = (char *)malloc((src_len + 1) * sizeof(char));
	if (!(dupstr))
		err_alloc();
	idx = 0;
	while (idx < src_len)
	{
		dupstr[idx] = s1[idx];
		idx++;
	}
	dupstr[idx] = '\0';
	return (dupstr);
}

char	*msh_strndup(char *str, int n)
{
	int		idx;
	int		src_len;
	char	*dupstr;

	src_len = (int)ft_strlen(str);
	if (src_len < n)
		dupstr = (char *)malloc((src_len + 1) * sizeof(char));
	else
		dupstr = (char *)malloc((n + 1) * sizeof(char));
	if (!(dupstr))
		err_alloc();
	idx = 0;
	while (idx < src_len && idx < n)
	{
		dupstr[idx] = str[idx];
		idx++;
	}
	dupstr[idx] = '\0';
	return (dupstr);
}

char	*msh_strjoin(char *s1, char *s2)
{
	size_t	total_len;
	char	*new_str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	new_str = (char *)malloc(total_len * sizeof(char));
	if (!new_str)
		err_alloc();
	new_str[0] = '\0';
	if (total_len != 1)
	{
		ft_strlcat(new_str, (char *)s1, ft_strlen(s1) + 1);
		ft_strlcat(new_str, (char *)s2, total_len);
	}
	free(s1);
	free(s2);
	return (new_str);
}
