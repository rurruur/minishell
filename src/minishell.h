/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:59:19 by jrim              #+#    #+#             */
/*   Updated: 2022/07/06 14:29:22 by jrim             ###   ########.fr       */
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

// parser가 executor에게 주는 선물은 다음과 같습니다...
typedef struct s_toklst
{
	t_token			*cmd;		//	cmd와 뒤에 오는 str들
	t_token			*infile;	//	< : infile name
	t_token			*outfile;	//	> : outfile name
	t_token			*here_doc;	//	<< : here_doc에 들어가는 str들
	t_token			*append;	//	>> : append 되어야할 file name
	struct s_toklst	*next;
} 					t_toklst;

typedef struct s_token
{
	char			*str;
	struct s_token	*next;
} 					t_token;
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