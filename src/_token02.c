/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _token02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 18:16:27 by jrim              #+#    #+#             */
/*   Updated: 2022/07/11 23:09:54 by nakkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*split_tok(char *line, char *delim);
void	parse_delim(char **line, char *delim, t_token **strlst);
void	assort_delim(t_token **new, char **line, int flag);
char	*make_strs(char **line, char *delim);

t_token	*split_tok(char *line, char *delim)
{
	char	*tmp;
	t_token	*strlst;

	strlst = NULL;
	while (*line != '\0')
	{
		parse_delim(&line, delim, &strlst);
		tmp = make_strs(&line, delim);
		while (!ft_strchr(delim, *line))
			tmp = msh_strjoin(tmp, make_strs(&line, delim));
		add_to_strlst(&strlst, init_strlst(tmp));
	}
	return (strlst);
}

void	parse_delim(char **line, char *delim, t_token **strlst)
{
	t_token	*new;

	while (ft_strchr(delim, **line) && **line != '\0')
	{
		new = NULL;
		if (!ft_strncmp(*line, "<<", 2) || !ft_strncmp(*line, ">>", 2))
			assort_delim(&new, line, 2);
		else if (ft_strchr("|<>", **line))
			assort_delim(&new, line, 1);
		if (new)
			add_to_strlst(strlst, new);
		(*line)++;
	}
}

void	assort_delim(t_token **new, char **line, int flag)
{
	(*new) = init_strlst(ft_strndup(*line, flag));
	if (flag == 2)	// << or >>
	{
		if (**line == '<')
			(*new)->type = T_RDR_HD;
		else if (**line == '>')
			(*new)->type = T_RDR_AP;
		(*line)++;
	}
	else			// < or > or |
	{
		if (flag == 1 && **line == '<')
			(*new)->type = T_RDR_IN;
		else if (flag == 1 && **line == '>')
			(*new)->type = T_RDR_OUT;
		else if (flag == 1 && **line == '|')
			(*new)->type = T_PIPE;
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
