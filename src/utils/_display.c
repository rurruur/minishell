/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _display.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 18:56:57 by jrim              #+#    #+#             */
/*   Updated: 2022/07/17 13:52:14 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	display_toklst(t_toklst *toklst);
void	display_strlst(t_token *strlst);
void	display_envlst(t_env *envlst);

void	display_toklst(t_toklst *toklst)
{
	int idx;

	idx = 1;
	while (toklst)
	{
		if (!toklst)
			break;
		printf("__________ %dth node __________\n", idx);
		printf("  cmd : ");
		display_strlst(toklst->cmd);
		printf(" </<<  : ");
		display_strlst(toklst->rdr_in);
		printf(" >/>> : ");
		display_strlst(toklst->rdr_out);
		printf("______________________________\n");
		toklst = toklst->next;
		idx++;
	}
}

void	display_strlst(t_token *strlst)
{
	if (!strlst)
		printf("(null)\n");
	while (strlst)
	{
		// printf("%s", strlst->str);
		printf("%s(%d)", strlst->str, strlst->type);
		if (strlst->next)
			printf(" | ");
		else
			printf(" \033[0;33m.\033[0;37m\n");
		strlst = strlst->next;
	}
}

void	display_envlst(t_env *envlst)
{
	if (!envlst)
		printf("(null)\n");
	while (envlst)
	{
		printf("%s=%s\n", envlst->key, envlst->val);
		envlst = envlst->next;
	}
}