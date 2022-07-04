/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:59:19 by jrim              #+#    #+#             */
/*   Updated: 2022/07/04 18:58:04 by jrim             ###   ########.fr       */
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

// parser가 executor에게 주는 선물은 다음과 같습니다...
typedef struct s_parsed
{
	t_chunk			node;	//	각 노드는 |를 기준으로 나누어져있습니다.
	struct s_parsed	*next;
} 	t_parsed;

typedef struct s_chunk
{
	int		in_rdr;		//	< 유무
	char	**infile;	//	infile name
	char	*cmd;		//	cmd일 것으로 예상되는 str
	char	**param;	//	cmd 뒤에 오는 str들의 배열
	int		out_rdr;	//	> 유무
	char	**outfile;	//	outfile name
	int		app_rdr;	//	>> 유무
	char	**appfile;	//	append 되어야할 file name
} 	t_chunk;
// char **의 경우 배열의 마지막은 NULL (ft_split처럼)
// 여기까지가 parser로부터의 선물입니다.

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
