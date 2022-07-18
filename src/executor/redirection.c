/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 23:05:18 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/18 21:20:29 by nakkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	set_infile_redirection(t_token *files)
{
	int	fd;
	int	exists;

	exists = 1;
	while (files)
	{
		if (exists && stat(files->str, NULL) == -1)
			exists = 0;
		if (files->next == NULL)
			break ;
		files = files->next;
	}
	if (!exists)
	{
		errno = NO_EXIST;
		ft_error(files->str);
	}
	fd = open(files->str, O_RDONLY);
	if (dup2(fd, STDIN_FILENO < 0))
		ft_error(files->str);
	close(fd);
}

static int	set_outfile_redirection(t_token *files)
{
	int	fd;

	while (files)
	{
		if (files->type == T_RDR_OUT)
			fd = open(files->str, O_WRONLY | O_TRUNC | O_CREAT, 0777);
		else if (files->type == T_RDR_AP)
			fd = open(files->str, O_WRONLY | O_APPEND | O_CREAT, 0777);
		if (fd < 0)
			ft_error(files->str);
		if (files->next == NULL)
			break ;
		close(fd);
		files = files->next;
	}
	if (dup2(fd, STDOUT_FILENO < 0))
		ft_error("dup2");
	close(fd);
	return (1);
}

void	set_redirection(t_toklst *list)
{
	if (list->rdr_in)
		set_infile_redirection(list->rdr_in);
	else if (list->prev)
	{
		if (dup2(list->prev->end[0], STDIN_FILENO) < 0)
			ft_error("dup2");
	}
	if (list->rdr_out)
		set_outfile_redirection(list->rdr_out);
	else if (list->next != NULL)
	{
		if (dup2(list->end[1], STDOUT_FILENO) < 0)
			ft_error("dup2");
	}
	close(list->end[0]);
	close(list->end[1]);
}
