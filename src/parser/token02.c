/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 18:16:27 by jrim              #+#    #+#             */
/*   Updated: 2022/07/23 01:22:17 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*split_tok(char *line, char *delim);
void	parse_delim(char **line, char *delim, t_token **strlst);
void	assort_delim(t_token **new, char **line, int flag);
char	*make_tok(char **line);
void	cnt_tok_len(char *line, int *len, int quote);

t_token	*split_tok(char *line, char *delim)
{
	char	*tmp;
	t_token	*strlst;

	strlst = NULL;
	while (*line != '\0')
	{
		parse_delim(&line, delim, &strlst);
		tmp = make_tok(&line);
		while (*line != '\0' && !ft_strchr(delim, *line))
			tmp = msh_strjoin(tmp, make_tok(&line));
		if (tmp)
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
	(*new) = init_strlst(msh_strndup(*line, flag));
	if (flag == 2)
	{
		if (**line == '<')
			(*new)->type = T_RDR_HD;
		else if (**line == '>')
			(*new)->type = T_RDR_AP;
		(*line)++;
	}
	else
	{
		if (flag == 1 && **line == '<')
			(*new)->type = T_RDR_IN;
		else if (flag == 1 && **line == '>')
			(*new)->type = T_RDR_OUT;
		else if (flag == 1 && **line == '|')
			(*new)->type = T_PIPE;
	}	
}

char	*make_tok(char **line)
{
	int		len;
	char	*str;

	if (**line == '\0')
		return (NULL);
	len = 0;
	if (**line != '"' && **line != '\'')
		cnt_tok_len(*line, &len, 0);
	else
		cnt_tok_len(*line, &len, 1);
	str = msh_strndup(*line, len);
	(*line) += len;
	return (str);
}

void	cnt_tok_len(char *line, int *len, int quote)
{
	if (quote == 1)
	{
		(*len)++;
		while (line[*len] != *line)
		{
			if (ft_strncmp(line + (*len), "\\\\", 2) == 0)
				(*len)++;
			else if (line[*len] == '\\' && ft_strchr(QUOTE, line[*len + 1]))
				(*len)++;
			(*len)++;
		}
		(*len)++;
	}
	else
	{
		while (line[*len] != '\0' && !ft_strchr(DELIM_WITH_QUOTE, line[*len]))
		{
			if (ft_strncmp(line + *len, "\\\\", 2) == 0)
				(*len)++;
			else if (line[*len] == '\\' && ft_strchr(QUOTE, line[*len + 1]))
				(*len)++;
			(*len)++;
		}
	}
}
