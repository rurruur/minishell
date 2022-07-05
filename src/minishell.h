/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:59:19 by jrim              #+#    #+#             */
/*   Updated: 2022/07/06 01:44:02 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

# include "../libft/libft.h"

# define PRMPT "( ´Д`)> "
# define QUOTE "'\""
# define RDR "<>"

typedef struct s_strlst
{
	char			*str;
	struct s_strlst *next;
} 	t_strlst;

// parser가 executor에게 주는 선물은 다음과 같습니다...
typedef struct s_token
{
	char		*cmd;		//	cmd일 것으로 예상되는 str
	t_strlst	*param;	//	cmd 뒤에 오는 str들의 배열
	int			rdr_in;		//	< 유무
	t_strlst	**infile;	//	infile name
	int			rdr_out;	//	> 유무
	t_strlst	**outfile;	//	outfile name
	int			here_doc;	//	>> 유무
	t_strlst	**hd_str;	//	here_doc에 들어가는 str들
	int			rdr_app;	//	>> 유무
	t_strlst	**appfile;	//	append 되어야할 file name
} 				t_token;

typedef struct s_toknd
{
	t_token			*content;	//	각 노드는 |를 기준으로 나누어져있습니다.
	struct s_tkoknd	*next;
} 	t_toknd;
// char **의 경우 배열의 마지막은 NULL (ft_split처럼)
// 여기까지가 parser로부터의 선물입니다.
// thank you from executor

// minishell.c

// _signal.c
void	h_sigint(int signum);
void	h_sigquit(int signum);

// _parser.c
void	parser_main(char *line, t_toknd *toklst);
int		check_quote(char *line);

// _tokenizer.c
char	**tok_split(char const *s, char c);
int		count_str(char const *s, char c);
void	make_strs(char **strs, int idx, char **ptr, char c);

// _token.c
t_token *trim_pretok(char **pretok, int *idx, t_toknd *toklst);
t_toknd	*init_toknd(t_token *content);
void	add_token(t_toknd **toklst, t_toknd *new);
char	*quote_trim(char *str);

// _utils.c
void	free_all(char **str);
void	err_msg(char *str);
char	*ft_strndup(char *str, int n);

#endif