/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:59:19 by jrim              #+#    #+#             */
/*   Updated: 2022/07/05 16:17:14 by jrim             ###   ########.fr       */
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

# include "../gnl/get_next_line.h"
# include "../libft/libft.h"

# define PRMPT "( ´Д`)> "
# define QUOTE "'\""
# define RDR

// typedef struct s_tokcnt
// {
// 	int	pipe;
// 	int	sq_cnt;
// 	int	dq_cnt;
// } 		t_tokcnt;

typedef struct s_strlst
{
	char			*str;
	struct s_strlst *next;
} 	t_strlst;

// parser가 executor에게 주는 선물은 다음과 같습니다...
typedef struct s_token
{
	char		*cmd;		//	cmd일 것으로 예상되는 str
	t_strlst	**param;	//	cmd 뒤에 오는 str들의 배열
	int			rdr_in;		//	< 유무
	t_strlst	**infile;	//	infile name
	int			rdr_out;	//	> 유무
	t_strlst	**outfile;	//	outfile name
	int			here_doc;	//	>> 유무
	t_strlst	**hd_str;	//	here_doc에 들어가는 str들
	int			rdr_app;	//	>> 유무
	t_strlst	**appfile;	//	append 되어야할 file name
} 				t_token;

typedef struct s_toklst
{
	t_token			node;	//	각 노드는 |를 기준으로 나누어져있습니다.
	struct s_tklst	*next;
} 	t_toklst;
// char **의 경우 배열의 마지막은 NULL (ft_split처럼)
// 여기까지가 parser로부터의 선물입니다.
// thank you from executor

// minishell.c

// _signal.c
void	h_sigint(int signum);
void	h_sigquit(int signum);

// _check.c
void	checker_main(char *line);
int		check_quote(char *line, char *key);
void	fill_key(char *line, char *key);
int		check_pipe(char *key);
int		check_rdr(char *key);

// _parser.c
void	parser_main(char *line, t_toklst *toklst);

// _token.c
void	init_token(t_token *tok);
void	tok_rdr(t_token *tok, int rdr_flag, char *content);
void	tok_cmd(t_token *tok, int cmd_flag, char *content);
void	add_token(t_toklst *toklst, t_token *tok);

// _utils.c
void	free_all(char **str);
void	err_msg(char *str);
int		skip_space(char *str);

#endif