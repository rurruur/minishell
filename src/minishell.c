/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:59:23 by jrim              #+#    #+#             */
/*   Updated: 2022/07/03 16:27:43 by nakkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void h_INT(int signum)
{
    if (signum != SIGINT)
        return;
    printf("ctrl + c print a new prompt on a newline\n");
    rl_on_new_line();
    rl_replace_line("", 1);
    rl_redisplay();
}

void h_QUIT(int signum)
{
    if (signum != SIGQUIT)
        return;
    printf("ctrl + \\ do nothing\n");
    rl_on_new_line();
    rl_replace_line("", 1);
    rl_redisplay();
}

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
            printf("%s%s\n", PRMPT, line);
            add_history(line);
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