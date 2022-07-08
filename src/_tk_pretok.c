/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tk_pretok.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 18:16:27 by jrim              #+#    #+#             */
/*   Updated: 2022/07/08 13:09:41 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tok_split(char *ptr, char c);
char	*make_strs(char **ptr, char c);
int		cnt_len(char **ptr, char c);

t_token	*tok_split(char *ptr, char c)
{
	char	*tmp;
	t_token	*strlst;

	strlst = NULL;
	while (*ptr != '\0')
	{
		while (*ptr == c && *ptr != '\0')
			ptr++;
		tmp = make_strs(&ptr, c);
		add_to_strlst(&strlst, init_token(tmp));
	}
	return (strlst);
}

char	*make_strs(char **ptr, char c)
{
	int		len;
	char	*str;

	len = cnt_len(ptr, c);
	// if (**ptr == '"' || **ptr == '\'')
	// {
	// 	len++;
	// 	while ((*ptr)[len] != **ptr)
	// 		len++;
	// 	len++; //closing quote
	// }
	// else
	// {
	// 	while ((*ptr)[len] != c && (*ptr)[len] != '"' && (*ptr)[len] != '\'' && (*ptr)[len] != '\0')
	// 		len++;
	// }
	str = ft_strndup(*ptr, len);
	(*ptr) += len;
	return (str);
}

int		cnt_len(char **ptr, char c)
{
	int len;

	len = 0;
	if (**ptr != '"' && **ptr != '\'')
		while ((*ptr)[len] != c && (*ptr)[len] != '\0')
			len++;
	else
	{
		len++;
		while ((*ptr)[len] != **ptr)
			len++;
		len++;
	}
	// printf("len : %d\n", len);
	return (len);	
}