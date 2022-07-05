/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parser_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:37:29 by jrim              #+#    #+#             */
/*   Updated: 2022/07/05 17:53:33 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	helper_main(char *line, char *key, char c);
int		searcher(char *line, char c);
char	*ft_strndup(const char *s1, int n);

void	helper_main(char *line, char *key, char c)
{
	int 	len;
	char	*str;

	len = 0;
	// skip_space
	len = searcher(line, c);
	str = ft_strndup(line, len);
	// node내용 추가
}

char	*ft_strndup(const char *s1, int n)
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