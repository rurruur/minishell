/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __display.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 18:56:57 by jrim              #+#    #+#             */
/*   Updated: 2022/07/11 21:45:29 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_toklst(t_toklst *toklst);
void	display_strlst(t_token *strlst);

void	display_toklst(t_toklst *toklst)
{
	int idx;

	idx = 1;
	while (toklst)
	{
		toklst = toklst->next;
		if (!toklst)
			break;
		printf("__________ %dth node __________\n", idx);
		printf("  cmd : ");
		display_strlst(toklst->cmd);
		printf("  rdr : ");
		display_strlst(toklst->rdr);
		printf("   <  : ");
		display_strlst(toklst->infile);
		printf("  <<  : ");
		display_strlst(toklst->heredoc);
		printf("   >  : ");
		display_strlst(toklst->outfile);
		printf("  >>  : ");
		display_strlst(toklst->append);
		printf("______________________________\n");
		idx++;
	}
}

void	display_strlst(t_token *strlst)
{
	if (!strlst)
		printf("(null)\n");
	while (strlst)
	{
		printf("%s", strlst->str);
		// printf("%s(%d)", strlst->str, strlst->type);
		if (strlst->next)
			printf(" | ");
		else
			printf(" \033[0;33m.\033[0;37m\n");
		strlst = strlst->next;
	}
}