/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:59:23 by jrim              #+#    #+#             */
/*   Updated: 2022/07/03 17:04:06 by nakkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
    char *line;

    signal(SIGINT, h_INT);      // ctrl + c
    signal(SIGQUIT, h_QUIT);    // ctrl + '\'
    while (1)
    {
        line = readline(PRMPT);
        if (line)
        {
            // printf("%s%s\n", PRMPT, line);
            add_history(line);

			// error check
			printf("%d\n", check_quote(line));

            free(line);
            line = NULL;
        }
        else // ctrl + d
        {
            printf("\b\bctrl + d exit the shell\n");
            break;
        }
    }
    return (0);
}
