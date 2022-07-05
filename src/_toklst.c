/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _token.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 00:30:47 by jrim              #+#    #+#             */
/*   Updated: 2022/07/05 21:33:05 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_token(t_token *tok);
void	tok_rdr(t_token *tok, int rdr_flag, char *content);	// flag : 0(<), 1(>), 2(<<), 3(>>)
void	tok_cmd(t_token *tok, int cmd_flag, char *content); // flag : 0(cmd), 1(param)
void	add_token(t_toklst *toklst, t_token *tok);