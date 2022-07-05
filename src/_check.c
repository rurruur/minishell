/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _check.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 17:01:52 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/05 16:25:14 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	checker_main(char *line);
int		check_quote(char *line, char *key);
void	fill_key(char *line, char *key);
int		check_pipe(char *key);
int		check_rdr(char *key);

void	checker_main(char *line)
{
	char	*key;
	size_t	idx;

	// (start) key_init
	key = (char *)malloc((ft_strlen(line) + 1) * sizeof(char));
	if (!key)
		err_msg("allocation");
	idx = 0;
	while (idx < ft_strlen(line))
	{
		*(key + idx) = '-';
		idx++;
	}
	*(key + idx) = '\0';
	// (end) key_init
	
	if (!check_quote(line, key))
		err_msg("quote");
	else
	{
		fill_key(line, key);
		if (!check_pipe(key))
			err_msg("pipe");
		if (!check_rdr(key))
			err_msg("rdr");
		else
			printf("key : %s\n", key);
	}
}


int	check_quote(char *line, char *key)
{
	int	sq_flag;	// single quote flag
	int	dq_flag;	// double quote flag

	sq_flag = 1;
	dq_flag = 1;
	while (*line)
	{
		if (ft_strncmp(line, "\\'", 2) == 0 || ft_strncmp(line, "\\\"", 2) == 0)
		{
			line += 2;
			key += 2;
			continue ;
		}
		if (dq_flag > 0 && *line == '\'')
		{
			sq_flag = -sq_flag;
			*key = '\'';
		}
		if (sq_flag > 0 && *line == '"')
		{
			dq_flag = -dq_flag;
			*key = '"';
		}
		if (dq_flag < 0)
			*key = '"';
		if (sq_flag < 0)
			*key = '\'';
		line++;
		key++;
	}
	return (sq_flag + dq_flag > 0); // flag가 -1이면 quote가 안닫혔다는 의미
}

void	fill_key(char *line, char *key)
{
	while (*line)
	{
		if (*key != '\'' && *key != '"')
		{
			if (*line == '|')
				*key = '|';
			else if (*line == '<')
				*key = '<';
			else if (*line == '>')
				*key = '>';
			else if (*line == ' ')
				*key = ' ';
		}
		line++;
		key++;
	}
}

int		check_pipe(char *key)
{
	// line += skip_space(line);
	// | cmd : parse error near `|'
	// | : parse error near `|'
	if (*key == '|')
	{
		key++;
		return (0);
	}
	while (*key)
	{
		//line += skip_space(line);
		// wrong_cmd | cmd : 뒤에만 실행해야함
		// cmd | wrong_cmd : command not found
		// cmd | : 더 받으려고 기다림
		key++;
	}
	return (1);
}

int		check_rdr(char *key)
{
	if (!ft_strnstr(key, "<<<", ft_strlen(key)))
		return (0);
	if (!ft_strnstr(key, ">>>", ft_strlen(key)))
		return (0);
	return (1);
}