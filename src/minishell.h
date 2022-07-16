/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:59:19 by jrim              #+#    #+#             */
/*   Updated: 2022/07/16 21:14:14 by jrim             ###   ########.fr       */
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
# define WH_SPACE " \f\n\r\t\v"
# define DELIM " <>|'\""
# define QUOTE "'\""
# define STR_DQ "\""
# define STR_SQ "\'"
// # define RDR "<>"

# define CLOSED 1
# define OPEN -1

int	g_fd;

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

typedef struct s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
} 					t_env;

typedef struct s_token
{
	char			*str;
	enum e_type		type;
	struct s_token	*next;
} 					t_token;

typedef struct s_toklst
{
	t_token			*cmd;		//	cmd와 뒤에 오는 str들
	t_token			*infile;	//	< : infile name
	t_token			*heredoc;	//	<< : here_doc에 들어가는 str들
	t_token			*rdr_out;
	t_token			*trash;
	int				end[2];
	t_env			*envlst;
	struct s_toklst	*next;
} 					t_toklst;

// _signal.c
void		handle_sig(void);
void		h_sigint(int signum);
void		h_sigquit(int signum);

// _check.c
int			check_whitespace(char *line);
int			check_quote(char *line);
int			check_pretok(t_token *pretok);
void		check_empty(t_token *pretok);

// _env.c
t_env		*copy_env(char **env, t_env *envlst);
void		is_env(t_token *pretok, t_env *envlst);
char		*insert_env(t_env *envlst, char *old, char *str, int start);
char		*find_env(t_env *envlst, char *key);
char		**get_env(t_env *envlst);

// _token01.c
t_toklst	*tokenizer(char *line, t_toklst *toklst, t_env *envlst);
int			pretoknizer(char *line, t_token **pretok, t_env *envlst);
void		tok_to_lst(t_token **pretok, t_toklst *new);

// _token02.c
t_token		*split_tok(char *line, char *delim);
void		parse_delim(char **line, char *delim, t_token **strlst);
void		assort_delim(t_token **new, char **line, int flag);
char		*make_tok(char **line, char *delim);

// _token03.c
void		trim_pretok(t_token *pretok);
char		*trim_quote(char *str);
int			cnt_trimmed_len(char *str);
void		del_quote_or_escape(char **str, int *q1, int *q2, int *len);

// _lst01.c
t_token		*init_strlst(char *content);
void		add_to_strlst(t_token **strlst, t_token *new);
void		del_from_strlst(t_token **strlst);
void		lst_to_lst(t_token **old, t_token **new);

// _lst02.c
t_env		*init_envlst(char *key, char *val);
void		add_to_envlst(t_env **envlst, t_env *new);
t_toklst	*init_toklst(t_env *envlst);
void		add_to_toklst(t_toklst **toklst, t_toklst *new);

// _free.c
void		free_strarr(char **str);
void		free_strlst(t_token *strlst);
void		free_envlst(t_env *envlst);
void		free_toklst(t_toklst *toklst);

// _error.c
void		print_errmsg(int err_type, char *str);
void		err_syntax(int err_type, char *str);
void		err_custom(int err_type, char *str);
void		err_alloc(void);

// _utils.c
char		*ft_strndup(char *str, int n);
char		*msh_strjoin(char *s1, char *s2);

// __display.c
void		display_toklst(t_toklst *toklst);
void		display_strlst(t_token *strlst);
void		display_envlst(t_env *envlst);

// executor/redirection.c
int			set_file_redirection(t_token *files, enum e_rdr mode);
void		set_redirection(t_toklst *list, int end);

// executor/executor.c
int			is_builtin(char *cmd);
void		child_process(t_toklst *list, int end, t_env *envlst);
void		parent_process(pid_t child, int *end);
void		executor(t_toklst *list, t_env *envlst);

// executor/cmd_utils.c
int			get_cmd_count(t_token *cmds);
char		**list_to_arr(t_token *cmds);
char		*double_strjoin(char *start, char *middle, char *end);
void		destroy_split(char **arr);
char		*get_valid_cmd_path(char *cmd, t_env *env);

// built-in functions
int			builtin_main(char *cmd, t_token *argv, t_env *envlst);
int			msh_cd(t_token *argv, t_env *envlst);
int			msh_echo(t_token *argv);
int			msh_env(t_token *argv, t_env *envlst);
int			msh_exit(t_token *argv);
int			msh_pwd(t_token *argv);
int			msh_unset(t_token *argv, t_env *envlst);
int			msh_export(t_token *argv, t_env *envlst);

#endif