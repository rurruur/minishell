/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 15:15:32 by jrim              #+#    #+#             */
/*   Updated: 2022/05/10 16:57:53 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*fill_depot(int fd, char *depot);
char	*trim_eol(char *depot);
char	*trim_depot(char *depot);

char	*get_next_line(int fd)
{
	static char	*depot;
	char		*one_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	depot = fill_depot(fd, depot);
	if (!depot || !(*depot))
	{
		free(depot);
		depot = 0;
		return (0);
	}
	one_line = trim_eol(depot);
	depot = trim_depot(depot);
	return (one_line);
}

char	*fill_depot(int fd, char *depot)
{
	char	*buf;
	int		byte;

	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (0);
	byte = 1;
	while (byte > 0 && gnl_strchr(depot, '\n') == 0)
	{
		byte = read(fd, buf, BUFFER_SIZE);
		if (byte == -1)
		{
			free(buf);
			buf = 0;
			return (0);
		}
		buf[byte] = '\0';
		depot = gnl_strjoin(depot, buf);
	}
	free(buf);
	buf = 0;
	return (depot);
}

char	*trim_eol(char *depot)
{
	int	eol_idx;

	if (gnl_strchr(depot, '\n') == 0)
		return (depot);
	eol_idx = (int)(gnl_strchr(depot, '\n') - depot);
	return (gnl_strndup(depot, eol_idx + 1));
}

char	*trim_depot(char *depot)
{
	int		eol_idx;
	int		trimmed_len;
	char	*new_depot;

	if (gnl_strchr(depot, '\n') == 0)
		return (0);
	eol_idx = (int)(gnl_strchr(depot, '\n') - depot);
	if (depot[eol_idx + 1] == '\0')
	{
		free(depot);
		depot = 0;
		return (0);
	}
	trimmed_len = gnl_strlen(depot) - (eol_idx + 1);
	new_depot = gnl_strndup(depot + eol_idx + 1, trimmed_len);
	free(depot);
	depot = 0;
	return (new_depot);
}
