/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:59:19 by jrim              #+#    #+#             */
/*   Updated: 2022/07/08 14:03:44 by jrim             ###   ########.fr       */
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

# define OFF 0;
# define RD_IN 1;
# define RD_OUT 2;
# define RD_HD 3;
# define RD_AP 4;
# define END -1;

// parser가 executor에게 주는 선물은 다음과 같습니다...
typedef struct s_token
{
	char			*str;
	int				flag;
	struct s_token	*next;
} 					t_token;

typedef struct s_toklst
{
	t_token			*cmd;		//	cmd와 뒤에 오는 str들
	t_token			*infile;	//	< : infile name
	t_token			*outfile;	//	> : outfile name
	t_token			*heredoc;	//	<< : here_doc에 들어가는 str들
	t_token			*append;	//	>> : append 되어야할 file name
	struct s_toklst	*next;
} 					t_toklst;
// char **의 경우 배열의 마지막은 NULL (ft_split처럼)
// 여기까지가 parser로부터의 선물입니다.
// thank you from executor

// minishell.c

// _signal.c
void	h_sigint(int signum);
void	h_sigquit(int signum);

// _parser.c
void	parser_main(char *line, t_toklst *toklst);
int		check_quote(char *line);

// _pretok.c
t_token	*tok_split(char *ptr, char *delim);
char	*make_strs(char **ptr, char *delim);
// char	**tok_split(char const *s, char c);
// int		count_str(char const *s, char c);
// void	make_strs(char **strs, int idx, char **ptr, char c);

// _tokenizer.c
void	tokenizer(t_token **pretok, t_toklst *new);
char	*quote_trim(char *str);

// _toklst.c
t_token		*init_token(char *content);
void		add_to_strlst(t_token **strlst, t_token *new);
t_toklst	*init_toklst(void);
void		add_to_toklst(t_toklst **toklst, t_toklst *new);

// _utils.c
void	free_all(char **str);
void	err_msg(char *str);
char	*ft_strndup(char *str, int n);

// _utils_display.c
void	display_toklst(t_toklst *toklst);
void	display_strlst(t_token *strlst);

#endif