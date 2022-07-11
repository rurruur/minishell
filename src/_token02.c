/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _token02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 18:16:27 by jrim              #+#    #+#             */
/*   Updated: 2022/07/11 18:16:45 by jrim             ###   ########.fr       */
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
			tmp = ft_strjoin(tmp, make_strs(&line, delim)); // leak어쩔건데
		add_to_strlst(&strlst, init_strlst(tmp));
	}
	return (strlst);
}

void	skip_delim(char **line, char *delim, t_token **strlst)
{
	t_token	*new;

	while (ft_strchr(delim, **line) && **line != '\0')
	{
		new = NULL;
		if (**line == '|')
		{
			new = init_strlst(ft_strdup("|"));
			new->type = T_PIPE;
			add_to_strlst(strlst, new);
		}
		else if (ft_strncmp(*line, "<<", 2) == 0)
		{
			new = init_strlst(ft_strdup("<<"));
			new->type = T_RDR_HD;
			add_to_strlst(strlst, new);
			(*line)++;
		}
		else if (ft_strncmp(*line, ">>", 2) == 0)
		{
			new = init_strlst(ft_strdup(">>"));
			new->type = T_RDR_AP;
			add_to_strlst(strlst, new);
			(*line)++;
		}
		else if (**line == '<')
		{
			new = init_strlst(ft_strdup("<"));
			new->type = T_RDR_IN;
			add_to_strlst(strlst, new);
		}
		else if (**line == '>')
		{
			new = init_strlst(ft_strdup(">"));
			new->type = T_RDR_OUT;
			add_to_strlst(strlst, new);
		}
		(*line)++;
	}
}

char	*make_strs(char **line, char *delim)
{
	int		len;
	char	*str;

	len = 0;
	if (**line != '"' && **line != '\'')
		while (!ft_strchr(delim, (*line)[len]) && !ft_strchr(QUOTE, (*line)[len]) && (*line)[len] != '\0')
		{
			if ((*line)[len] == '\\' && ((*line)[len + 1] == '\'' || (*line)[len + 1] == '"'))
				len++;
			len++;
		}
	else
	{
		len++;
		while ((*line)[len] != **line)
		{
			if ((*line)[len] == '\\' && ((*line)[len + 1] == '\'' || (*line)[len + 1] == '"'))
				len++;
			len++;
		}
		len++;
	}
	str = ft_strndup(*line, len);
	(*line) += len;
	return (str);
}
