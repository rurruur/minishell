/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:59:19 by jrim              #+#    #+#             */
/*   Updated: 2022/07/11 23:03:10 by nakkim           ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/stat.h>

# include "../libft/libft.h"

# define PRMPT "\033[0;33m( ´Д`)>\033[0;37m "
# define QUOTE "'\""
# define STR_DQ "\""
# define STR_SQ "\'"
// # define RDR "<>"

# define CLOSED -1
# define OPEN 1

enum e_type
{
	T_OFF,
	T_RDR_IN,
	T_RDR_HD,
	T_RDR_OUT,
	T_RDR_AP,
	T_PIPE
};

enum e_rdr
{
	IN,
	OUT
};

typedef struct s_token
{
	char			*str;
	enum e_type		type;
	struct s_token	*next;
} 					t_token;

typedef struct s_toklst
{
	t_token			*cmd;		//	cmd와 뒤에 오는 str들
	t_token			*rdr;
	t_token			*infile;	//	< : infile name
	t_token			*heredoc;	//	<< : here_doc에 들어가는 str들
	t_token			*outfile;	//	> : outfile name
	t_token			*append;	//	>> : append 되어야할 file name
	struct s_toklst	*next;
} 					t_toklst;

// _signal.c
void		h_sigint(int signum);
void		h_sigquit(int signum);

// _check.c
int			check_quote(char *line);
int			check_pretok(t_token *pretok);

// _token01.c
void		tokenizer(char *line, t_toklst *toklst);
void		del_empty_tok(t_token *pretok);
void		tok_to_lst(t_token **pretok, t_toklst *new);

// _token02.c
t_token		*split_tok(char *line, char *delim);
void		parse_delim(char **line, char *delim, t_token **strlst);
void		assort_delim(t_token **new, char **line, int flag);
char		*make_strs(char **line, char *delim);

// _token03.c
void		trim_pretok(t_token *pretok);
char		*trim_quote(char *str);
int			check_len(char *str);

// _lst01.c
t_token		*init_strlst(char *content);
void		add_to_strlst(t_token **strlst, t_token *new);
void		del_from_strlst(t_token **strlst);
void		lst_to_lst(t_token **old, t_token **new);
void		free_strlst(t_token **strlst);

// _lst02.c
t_toklst	*init_toklst(void);
void		add_to_toklst(t_toklst **toklst, t_toklst *new);
void		free_toklst(t_toklst **toklst);

// _utils.c
void		free_all(char **str);
void		err_msg(char *str);
char		*ft_strndup(char *str, int n);
char		*msh_strjoin(char *s1, char *s2);

// __display.c
void		display_toklst(t_toklst *toklst);
void		display_strlst(t_token *strlst);

// executor.c
int		set_file_redirection(t_token *files, enum e_rdr mode);
void	set_redirection(t_toklst *list, int *end);
void	child_process(t_toklst *list, int *end, char **env);
void	parent_process(pid_t child, int *end);
void	executor(t_toklst *list, char **env);
int		get_cmd_count(t_token *cmds);
char	**list_to_arr(t_token *cmds);
char	*double_strjoin(char *start, char *middle, char *end);
char	*get_valid_cmd_path(char *cmd);

#endif