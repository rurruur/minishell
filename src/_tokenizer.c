/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tokenizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 18:16:27 by jrim              #+#    #+#             */
/*   Updated: 2022/07/05 21:07:08 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

void	tokenizer(char *line);
char	**tok_split(char const *s, char c);
int		count_str(char const *s, char c);
void	make_strs(char **strs, int idx, char **ptr, char c);

void	tokenizer(char *line)
{
	// ft_split 먼저 해서 받은 결과를 제대로된 토큰으로 만들어야함
	// quote 부분은 strjoin을 해서 리스트에 추가해야함
	// 리스트에 추가할 때는 flag를 통해서 해당 노드의 속성을 나타내주도록 해야함.
	char	**tokens;

	tokens = tok_split(line, ' ');
	for (int i = 0; tokens[i]; i++)
		printf("%s\n", tokens[i]);
	free_all(tokens);
	tokens = NULL;
}

char	**tok_split(char const *s, char c)
{
	char	**strs;
	char	*ptr;
	int		idx;
	int		str_cnt;

	if (!s)
		return (0);
	ptr = (char *)s;
	str_cnt = count_str(s, c) + 1;
	strs = (char **)malloc(str_cnt * sizeof(char *));
	if (!(strs))
		return (0);
	idx = 0;
	while (idx < str_cnt - 1 && *ptr != '\0')
	{
		while (*ptr == c && *ptr != '\0')
			ptr++;
		// printf("str : %s\n", ptr);
		make_strs(strs, idx, &ptr, c);
		if (!(strs))
			return (0);
		idx++;
	}
	strs[idx] = 0;
	return (strs);
}

int	count_str(char const *s, char c)
{
	int	idx;
	int	cnt;
	int	flag;
	int quote;

	idx = 0;
	cnt = 0;
	flag = 1;
	quote = 0;
	while (s[idx] != '\0')
	{
		if (quote == 0 && (s[idx] == '"' || s[idx] == '\''))
		{
			cnt++;
			quote = 1;
		}
		else if (s[idx] != c && flag == 1 && quote == 0)
		{
			cnt++;
			flag = 0;
		}
		else if (s[idx] == c && flag == 0 && quote == 0)
			flag = 1;
		else if (quote == 1 && (s[idx] == '"' || s[idx] == '\''))
		{
			quote = 0;
			flag = 1;
		}
		idx++;
	}
	// printf("cnt : %d\n", cnt);
	return (cnt);
}

void	make_strs(char **strs, int idx, char **ptr, char c)
{
	int	len;
	int	x;

	len = 0;
	if (**ptr == '"' || **ptr == '\'')
	{
		len++;
		while ((*ptr)[len] != **ptr)
			len++;
		len++; //closing quote
	}
	else
	{
		while ((*ptr)[len] != c && (*ptr)[len] != '"' && (*ptr)[len] != '\'' && (*ptr)[len] != '\0')
			len++;
	}
	// printf("len : %d\n", len);
	
	strs[idx] = (char *)malloc((len + 1) * sizeof(char));
	if (!(strs[idx]))
	{
		while (idx-- > 0)
			free (strs[idx]);
		free (strs);
		return ;
	}
	
	x = 0;
	while (x < len)
	{
		strs[idx][x] = **(ptr);
		x++;
		(*ptr)++;
	}
	strs[idx][x] = '\0';
}
