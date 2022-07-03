/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:59:23 by jrim              #+#    #+#             */
/*   Updated: 2022/07/03 17:23:49 by jrim             ###   ########.fr       */
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
            add_history(line);

			// error check
            if (!check_quote(line))
    			printf("quote error\n");
            else
                printf("%s%s\n", PRMPT, line);

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
