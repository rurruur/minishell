/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:59:19 by jrim              #+#    #+#             */
/*   Updated: 2022/07/04 00:07:33 by jrim             ###   ########.fr       */
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

typedef struct s_cmd
{
	
} t_cmd;

// minishell.c

// _signal.c
void	h_INT(int signum);
void	h_QUIT(int signum);

// _check.c
int		check_quote(char *line);
int		check_pipe(char **cmd_token);
int		check_RDR(char *line);

// _utils.c
void	free_all(char **str);
void	err_prompt(char *str);

#endif