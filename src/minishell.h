/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:59:19 by jrim              #+#    #+#             */
/*   Updated: 2022/07/22 22:07:16 by nakkim           ###   ########.fr       */
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
# include <string.h>
# include <limits.h>

# include "../libft/libft.h"

# define PRMPT "\033[0;33m( ´Д`)>\033[0;37m "
# define WH_SPACE " \f\n\r\t\v"
# define DELIM_WITH_QUOTE " <>|'\""
# define QUOTE "'\""

# define CLOSED 1
# define OPEN -1

# define ERR_QUOTE 0
# define ERR_SYNTAX 1
# define ERR_MEM 2

# define MAX_PATH_LEN 4096	// Linux maximum path length
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
void		display_toklst(t_toklst *toklst);
void		display_strlst(t_token *strlst);
void		display_envlst(t_env *envlst);
// env01.c
t_env		*copy_env(char **env, t_env *envlst);
void		env_to_str(t_token *pretok, t_env *envlst);
char		*insert_env(t_env *envlst, char *old, char *str);
// env02.c
char		*get_env_key(char *str);
char		*get_env_val(t_env *envlst, char *key);
int			find_env_val(t_env *envlst, char *key);
int			change_env_val(t_env *envlst, char *key, char *new_val);
char		**envlst_to_arr(t_env *envlst);
// error.c
void		err_parser(int err_type);
void		err_alloc(void);
// signal.c
void		handle_sig(enum e_sig_mode mode);
void		h_sigint(int signum);
void		h_sigquit(int signum);
// utils_str.c
char		*ft_strndup(char *str, int n);
char		*msh_strjoin(char *s1, char *s2);
int			ft_strcmp(const char *s1, const char *s2);
void		free_strarr(char **str);

/* directory: parser ----------------------------------------------------- */
// check.c
int			check_whitespace(char *line);
int			check_quote(char *line);
int			check_pretok(t_token *pretok);
// token01.c
t_toklst	*tokenizer(char *line, t_toklst *toklst, t_env *envlst);
int			pretoknizer(char *line, t_token **pretok, t_env *envlst);
void		tok_to_lst(t_token **pretok, t_toklst *new);
// token02.c
t_token		*split_tok(char *line, char *delim);
void		parse_delim(char **line, char *delim, t_token **strlst);
void		assort_delim(t_token **new, char **line, int flag);
char		*make_tok(char **line);
void		cnt_tok_len(char *line, int *len, int quote);
// token03.c
void		trim_pretok(t_token *pretok);
char		*trim_quote(char *str);
int			cnt_trimmed_len(char *str);
void		del_quote_or_escape(char **str, int *q1, int *q2, int *len);

/* directory: lst --------------------------------------------------------- */
// strlst.c
t_token		*init_strlst(char *content);
void		add_to_strlst(t_token **strlst, t_token *new);
void		del_from_strlst(t_token **strlst);
void		lst_to_lst(t_token **old, t_token **new);
void		free_strlst(t_token *strlst);
// toklst.c
t_toklst	*init_toklst(t_env *envlst);
void		add_to_toklst(t_toklst **toklst, t_toklst *new);
void		free_toklst(t_toklst *toklst);
// envlst.c
t_env		*init_envlst(char *key, char *val);
void		add_to_envlst(t_env **envlst, t_env *new);
void		del_from_envlst(t_env **envlst);
void		free_envlst(t_env *envlst);

/* directory: executor ---------------------------------------------------- */
// redirection.c
void		set_infile_redirection(t_token *files);
void		set_outfile_redirection(t_token *files);
int			set_file_redirection(t_token *files, enum e_rdr mode);
void		set_redirection(t_toklst *list);
// executor.c
void		child_process(t_toklst *list, t_env *envlst);
void		executor(t_toklst *list, t_env *envlst);
// cmd_utils.c
int			get_cmd_count(t_token *cmds);
char		**list_to_arr(t_token *cmds);
char		*double_strjoin(char *start, char *middle, char *end);
void		destroy_split(char **arr);
void		get_valid_cmd_path(char *cmd, t_env *env, char **cmd_path);
// heredoc.c
char		*make_file_name(char *heredoc);
int			process_heredoc(t_token *heredoc_tok, char *filename);
int			check_heredoc(t_toklst *list);
void		clear_heredoc(t_toklst *list);
// error.c
void		ft_error(char *err_msg);
// wait.c
void		ft_wait(t_toklst *list);

/* directory: builtin ----------------------------------------------------- */
// builtin functions
enum e_builtin	get_builtin_type(t_token *cmd, t_toklst *toklst);
void		builtin_main(t_token *argv, t_env *envlst, enum e_builtin cmd);
void		builtin_error(char *err_msg);
int			msh_cd(t_token *argv, t_env *envlst);
int			msh_echo(t_token *argv);
int			msh_env(t_token *argv, t_env *envlst);
int			msh_exit(t_token *argv, int type);
int			msh_pwd(t_token *argv);
int			msh_unset(t_token *argv, t_env *envlst);
int			msh_export(t_token *argv, t_env *envlst);

#endif