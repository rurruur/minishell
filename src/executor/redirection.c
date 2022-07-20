/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 23:05:18 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/20 17:02:34 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	set_infile_redirection(t_token *files)
{
	int			fd;
	struct stat	info;

	while (files)
	{
		if (stat(files->str, &info) == -1)
		{
			errno = NO_EXIST;
			ft_error(files->str);
		}
		if (files->next == NULL)
			break ;
		files = files->next;
	}
	fd = open(files->str, O_RDONLY);
	if (dup2(fd, STDIN_FILENO) < 0)
		ft_error(files->str);
	dprintf(g_fd, "infile: %s\n", files->str);
	close(fd);
}

static int	set_outfile_redirection(t_token *files)
{
	int	fd;

	while (files)
	{
		if (files->type == T_RDR_OUT)
			fd = open(files->str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else if (files->type == T_RDR_AP)
			fd = open(files->str, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (fd < 0)
			ft_error(files->str);
		dprintf(g_fd, "next outfile: %p\n", files->next);
		if (files->next == NULL)
			break ;
		close(fd);
		files = files->next;
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
		ft_error("dup2");
	close(fd);
	dprintf(g_fd, "outfile: %s\n", files->str);
	return (1);
}

void	set_redirection(t_toklst *list)
{
	if (list->prev)
	{
		if (dup2(list->prev->end[0], STDIN_FILENO) < 0)
			ft_error("dup2");
		dprintf(g_fd, "stdin\n");
	}
	if (list->rdr_in)
		set_infile_redirection(list->rdr_in);
	if (list->next != NULL)
	{
		if (dup2(list->end[1], STDOUT_FILENO) < 0)
			ft_error("dup2");
		dprintf(g_fd, "stdout\n");
	}
	if (list->rdr_out)
		set_outfile_redirection(list->rdr_out);
	close(list->end[0]);
	close(list->end[1]);
}
