/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 18:56:57 by jrim              #+#    #+#             */
/*   Updated: 2022/07/08 11:49:43 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_toklst(t_toklst *toklst);
void	display_strlst(t_token *strlst);

void	display_toklst(t_toklst *toklst)
{
	int idx;

	idx = 1;
	while (toklst->next)
	{
		toklst = toklst->next;
		printf("__________ %dth node __________\n", idx);
		printf("  cmd : ");
		display_strlst(toklst->cmd);
		printf("   <  : ");
		display_strlst(toklst->infile);
		printf("   >  : ");
		display_strlst(toklst->outfile);
		printf("  <<  : ");
		display_strlst(toklst->heredoc);
		printf("  >>  : ");
		display_strlst(toklst->append);
		printf("______________________________\n");
		idx++;
	}
}

void	display_strlst(t_token *strlst)
{
	while (strlst)
	{
		printf("%s", strlst->str);
		printf(" -> ");
		strlst = strlst->next;
	}
	printf("(null)\n");
}