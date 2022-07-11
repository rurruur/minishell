/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 21:16:48 by jrim              #+#    #+#             */
/*   Updated: 2022/07/11 23:15:58 by nakkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			count_str(char const *s, char c);
static void	make_strs(char **strs, int idx, char **ptr, char c);

char	**ft_split(char const *s, char c)
{
	char	**strs;
	char	*ptr;
	int		idx;
	int		str_cnt;

	if (!s)
		return (0);
	ptr = (char *)s;
	str_cnt = count_str(s, c) + 1;
	strs = (char **)malloc(str_cnt * sizeof(char *));
	if (!(strs))
		return (0);
	idx = 0;
	while (idx < str_cnt - 1 && *ptr != '\0')
	{
		while (*ptr == c && *ptr != '\0')
			ptr++;
		make_strs(strs, idx, &ptr, c);
		if (!(strs))
			return (0);
		idx++;
	}
	strs[idx] = 0;
	return (strs);
}

int	count_str(char const *s, char c)
{
	int	idx;
	int	cnt;
	int	flag;

	idx = 0;
	cnt = 0;
	flag = 1;
	while (s[idx] != '\0')
	{
		if (s[idx] != c && flag == 1)
		{
			cnt++;
			flag = 0;
		}
		else if (s[idx] == c && flag == 0)
			flag = 1;
		idx++;
	}
	return (cnt);
}

void	make_strs(char **strs, int idx, char **ptr, char c)
{
	int	len;

	len = 0;
	while ((*ptr)[len] != c && (*ptr)[len] != '\0')
		len++;
	strs[idx] = (char *)malloc((len + 1) * sizeof(char));
	if (!(strs[idx]))
	{
		while (idx-- > 0)
			free (strs[idx]);
		free (strs);
		return ;
	}
	len = 0;
	while (**ptr != c && **ptr != '\0')
	{
		strs[idx][len] = **(ptr);
		len++;
		(*ptr)++;
	}
	strs[idx][len] = '\0';
}
