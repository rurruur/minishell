/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _token02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 18:16:27 by jrim              #+#    #+#             */
/*   Updated: 2022/07/09 14:17:16 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tok_split(char *ptr, char *delim);
void	skip_delim(char **ptr, char *delim, t_token **strlst);
char	*make_strs(char **ptr, char *delim);
int		cnt_len(char **ptr, char *delim);

t_token	*tok_split(char *ptr, char *delim)
{
	char	*tmp;
	t_token	*strlst;

	strlst = NULL;
	while (*ptr != '\0')
	{
		skip_delim(&ptr, delim, &strlst);
		tmp = make_strs(&ptr, delim);
		while (!ft_strchr(delim, *ptr))
			tmp = ft_strjoin(tmp, make_strs(&ptr, delim));
		add_to_strlst(&strlst, init_token(tmp));
	}
	return (strlst);
}

void	skip_delim(char **ptr, char *delim, t_token **strlst)
{
	while (ft_strchr(delim, **ptr) && **ptr != '\0')
	{
		if (**ptr == '|')
			add_to_strlst(strlst, init_token("|"));
		else if (**ptr == '<')
		{
			if (*(*ptr + 1) == '<')
			{
				add_to_strlst(strlst, init_token("<<"));
				(*ptr)++;
			}
			else
				add_to_strlst(strlst, init_token("<"));
		}
		else if (**ptr == '>')
		{
			if (*(*ptr + 1) == '>')
			{
				add_to_strlst(strlst, init_token(">>"));
				(*ptr)++;
			}
			else
				add_to_strlst(strlst, init_token(">"));
		}
		(*ptr)++;
	}
}

char	*make_strs(char **ptr, char *delim)
{
	int		len;
	char	*str;

	len = cnt_len(ptr, delim);
	str = ft_strndup(*ptr, len);
	(*ptr) += len;
	return (str);
}

int		cnt_len(char **ptr, char *delim)
{
	int len;

	len = 0;
	if (**ptr != '"' && **ptr != '\'')
		while (!ft_strchr(delim, (*ptr)[len]) && !ft_strchr(QUOTE, (*ptr)[len]) && (*ptr)[len] != '\0')
			len++;
	else
	{
		len++;
		while ((*ptr)[len] != **ptr)
			len++;
		len++;
	}
	return (len);	
}
