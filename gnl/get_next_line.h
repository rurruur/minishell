/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 15:15:35 by jrim              #+#    #+#             */
/*   Updated: 2022/05/10 16:58:25 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

char	*get_next_line(int fd);
char	*fill_depot(int fd, char *depot);
char	*trim_eol(char *depot);
char	*trim_depot(char *depot);

char	*gnl_strchr(const char *s, int c);
char	*gnl_strjoin(char *s1, char *s2);
size_t	gnl_strlen(const char *s);
size_t	gnl_strlcat(char *dst, const char *src, size_t dstsize);
char	*gnl_strndup(const char *s1, size_t n);

#endif
