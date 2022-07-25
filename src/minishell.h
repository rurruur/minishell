/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:59:19 by jrim              #+#    #+#             */
/*   Updated: 2022/07/25 12:41:37 by jrim             ###   ########.fr       */
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
# include <sys/errno.h>

# include "../libft/libft.h"

# define PRMPT "gumshell> "
# define WH_SPACE " \f\n\r\t\v"
# define DELIM_WITH_QUOTE " <>|'\""
# define QUOTE "'\""

# define CLOSED 1
# define OPEN -1

# define VALID 1
# define INVALID 0

# define SUCCESS 1
# define FAILURE 0

# define ERR_QUOTE 0
# define ERR_SYNTAX 1

# define CD_NOT_SET 1
# define CD_NOT_FOUND 2
# define CD_NOT_DIR 3

# define LLONG_MAX 9223372036854775807
# define MAX_PATH_LEN 4096
# define MAX_ERRNO 255
# define CMD_NOT_FOUND 382
# define IS_DIR 381
# define NO_EXIST 256

# define CONTINUE 1
# define STOP 0

int	g_status;

enum e_builtin
{
	NONE,
	CD,
	ECHO,
	ENV,
	EXIT,
	EXIT_PIPE,
	PWD,
	UNSET,
	EXPORT
};

enum e_sig_mode
{
	READLINE,
	HEREDOC,
	SIG_WAIT
};

enum e_type
{
	T_ENV,
	T_OFF,
	T_PIPE,
	T_RDR_IN,
	T_RDR_HD,
	T_RDR_OUT,
	T_RDR_AP
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
	struct s_env	*prev;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	char			*str;
	enum e_type		type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_toklst
{
	pid_t			pid;
	t_token			*cmd;
	t_token			*rdr_in;
	t_token			*rdr_out;
	int				end[2];
	t_env			*envlst;
	struct s_toklst	*prev;
	struct s_toklst	*next;
}					t_toklst;

/* directory: utils ------------------------------------------------------ */
// _display.c
void			display_toklst(t_toklst *toklst);
void			display_strlst(t_token *strlst);
void			display_envlst(t_env *envlst);
// env01.c
t_env			*copy_env(char **env, t_env *envlst);
void			env_to_str(t_token *pretok, t_env *envlst);
void			skip_quote(char *str, int *idx, int *sq);
char			*insert_env(t_env *envlst, char *old, char *str);
char			**envlst_to_arr(t_env *envlst);
// env02.c
char			*get_env_key(char *str);
char			*get_env_val(t_env *envlst, char *key);
int				find_env_val(t_env *envlst, char *key);
int				change_env_val(t_env *envlst, char *key, char *new_val);
// error.c
void			err_parser(int err_type);
void			err_alloc(void);
// signal.c
void			handle_sig(enum e_sig_mode mode);
void			h_sigint(int signum);
void			h_sigquit(int signum);
// string.c
int				ft_strcmp(const char *s1, const char *s2);
char			*msh_strdup(char *s1);
char			*msh_strndup(char *str, int n);
char			*msh_strjoin(char *s1, char *s2);

/* directory: parser ----------------------------------------------------- */
// check.c
int				check_whitespace(char *line);
int				check_quote(char *line);
int				check_pretok(t_token *pretok);
// token01.c
t_toklst		*tokenizer(char *line, t_toklst *toklst, t_env *envlst);
int				pretoknizer(char *line, t_token **pretok, t_env *envlst);
void			tok_to_lst(t_token **pretok, t_toklst *new);
// token02.c
t_token			*split_tok(char *line, char *delim);
void			parse_delim(char **line, char *delim, t_token **strlst);
void			assort_delim(t_token **new, char **line, int flag);
char			*make_tok(char **line);
void			cnt_tok_len(char *line, int *len, int quote);
// token03.c
void			trim_pretok(t_token *pretok);
char			*trim_quote(char *str);
int				cnt_trimmed_len(char *str);
void			del_quote_or_escape(char **str, int *q1, int *q2, int *len);

/* directory: lst --------------------------------------------------------- */
// strlst.c
t_token			*init_strlst(char *content);
void			add_to_strlst(t_token **strlst, t_token *new);
void			del_from_strlst(t_token **strlst);
void			lst_to_lst(t_token **old, t_token **new);
void			free_strlst(t_token *strlst);
// toklst.c
t_toklst		*init_toklst(t_env *envlst);
void			add_to_toklst(t_toklst **toklst, t_toklst *new);
void			free_toklst(t_toklst *toklst);
// envlst.c
t_env			*init_envlst(char *key, char *val);
void			add_to_envlst(t_env **envlst, t_env *new);
void			del_from_envlst(t_env **envlst);
void			free_envlst(t_env *envlst);

/* directory: executor ---------------------------------------------------- */
// check_files.c
void			check_files(t_toklst *list);
int				check_infiles(t_token *files);
int				check_outfiles(t_token *files);
char			**get_env_path(t_env *env, char *cmd);
// redirection.c
void			set_infile_redirection(t_token *files);
void			set_outfile_redirection(t_token *files);
int				set_file_redirection(t_token *files, enum e_rdr mode);
void			set_redirection(t_toklst *list);
// executor.c
void			child_process(t_toklst *list, t_env *envlst);
int				get_pipe_count(t_toklst *list);
void			executor(t_toklst *list, t_env *envlst);
// cmd_utils.c
int				get_cmd_count(t_token *cmds);
char			**list_to_arr(t_token *cmds);
void			destroy_split(char **arr);
void			get_valid_cmd_path(char *cmd, t_env *env, char **cmd_path);
// heredoc.c
char			*make_file_name(int num);
int				process_heredoc(t_token *heredoc_tok, char *filename);
int				check_heredoc(t_toklst *list);
void			clear_heredoc(t_toklst *list);
// error.c
void			ft_error(char *err_msg);
void			ft_file_error(char *err_msg);
// wait.c
void			ft_wait(t_toklst *list);
// double_join.c
char			*double_strjoin(char *start, char *middle, char *end);

/* directory: builtin ----------------------------------------------------- */
// builtin functions
enum e_builtin	get_builtin_type(t_token *cmd, t_toklst *toklst);
void			builtin_main(t_token *argv, t_env *envlst, enum e_builtin cmd);
void			builtin_error(char *err_msg);
void			msh_cd(t_token *argv, t_env *envlst);
void			msh_echo(t_token *argv);
void			msh_env(t_token *argv, t_env *envlst);
void			msh_exit(t_token *argv, int type);
void			msh_pwd(void);
void			msh_unset(t_token *argv, t_env *envlst);
void			msh_export(t_token *argv, t_env *envlst);

#endif