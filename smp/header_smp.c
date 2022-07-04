/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_smp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:59:19 by jrim              #+#    #+#             */
/*   Updated: 2022/07/04 15:54:13 by jrim             ###   ########.fr       */
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

enum e_tok
{
    TK_STR,      // str -> cmd?
	TK_DQ_STR,   // "str"
	TK_SQ_STR,    // 'str'
	TK_IRD,      // Input Redirection : <
	TK_ORD,      // Output Redirection : >
	TK_HRD,      // Heredoc Redirection : <<
	TK_ARD,      // Append Redirection : >>
	TK_PIPE,     // |
	TK_AND,      // &&
	TK_OR,       // ||
	TK_LBR,      // Left Bracket : (
	TK_RBR,      // Right BRacket : )
	TK_ERR,      // invalid -> error
};

typedef struct s_tok
{
    enum e_tok  type;
    char        *content;
    t_list      *params;
} 				t_tok;

typedef enum e_tknzr_state
{
	T_BLANK, 	// 공백
	T_CHARS, 	// 글자
	T_SQUOTE,	// '
	T_DQUOTE, 	// "
	T_SMETA,  	// >, <, |
	T_DMETA,   	// <<, >>
	T_NONLI		// &&, ||
}	t_tknzr_state;

typedef struct s_tknzr
{
	t_tknzr_state	state;
	char			*buf;
	t_tok			*tokens;
}	t_tknzer;

// minishell.c

// _signal.c
void	h_sigint(int signum);
void	h_sigquit(int signum);

// _check.c
int		check_quote(char *line);
int		check_pipe(char **cmd_token);
int		check_RDR(char *line);

// _utils.c
void	free_all(char **str);
void	err_msg(char *str);

#endif
