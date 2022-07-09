/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _token02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 18:16:27 by jrim              #+#    #+#             */
/*   Updated: 2022/07/09 14:41:16 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*split_tok(char *line, char *delim);
void	skip_delim(char **line, char *delim, t_token **strlst);
char	*make_strs(char **line, char *delim);

t_token	*split_tok(char *line, char *delim)
{
	char	*tmp;
	t_token	*strlst;

	strlst = NULL;
	while (*line != '\0')
	{
		skip_delim(&line, delim, &strlst);
		tmp = make_strs(&line, delim);
		while (!ft_strchr(delim, *line))
			tmp = ft_strjoin(tmp, make_strs(&line, delim));
		add_to_strlst(&strlst, init_token(tmp));
	}
	return (strlst);
}

void	skip_delim(char **line, char *delim, t_token **strlst)
{
	while (ft_strchr(delim, **line) && **line != '\0')
	{
		if (**line == '|')
			add_to_strlst(strlst, init_token("|"));
		else if (ft_strncmp(*line, "<<", 2) == 0)
		{
			add_to_strlst(strlst, init_token("<<"));
			(*line)++;
		}
		else if (ft_strncmp(*line, ">>", 2) == 0)
		{
			add_to_strlst(strlst, init_token(">>"));
			(*line)++;
		}
		else if (**line == '<')
			add_to_strlst(strlst, init_token("<"));
		else if (**line == '>')
			add_to_strlst(strlst, init_token(">"));
		(*line)++;
	}
}

char	*make_strs(char **line, char *delim)
{
	int		len;
	char	*str;

	len = 0;
	if (**line != '"' && **line != '\'')
	{
		while (!ft_strchr(delim, (*line)[len]) && !ft_strchr(QUOTE, (*line)[len]) && (*line)[len] != '\0')
			len++;
	}
	else
	{
		len++;
		while ((*line)[len] != **line)
			len++;
		len++;
	}
	str = ft_strndup(*line, len);
	(*line) += len;
	return (str);
}
