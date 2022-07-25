/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 23:05:18 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/23 18:10:27 by nakkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_infile_redirection(t_token *files)
{
	int			fd;

	while (files)
	{
		if (files->next == NULL)
			break ;
		files = files->next;
	}
	fd = open(files->str, O_RDONLY);
	if (dup2(fd, STDIN_FILENO) < 0)
		ft_error(files->str);
	close(fd);
}

void	set_outfile_redirection(t_token *files)
{
	int	fd;

	while (files)
	{
		if (files->next == NULL)
			break ;
		files = files->next;
	}
	if (files->type == T_RDR_OUT)
		fd = open(files->str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		fd = open(files->str, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd < 0)
		ft_error(files->str);
	if (dup2(fd, STDOUT_FILENO) < 0)
		ft_error(files->str);
	close(fd);
}

void	set_redirection(t_toklst *list)
{
	if (list->prev)
	{
		if (dup2(list->prev->end[0], STDIN_FILENO) < 0)
			ft_error("dup2");
	}
	if (list->rdr_in)
		set_infile_redirection(list->rdr_in);
	if (list->next != NULL)
	{
		if (dup2(list->end[1], STDOUT_FILENO) < 0)
			ft_error("dup2");
	}
	if (list->rdr_out)
		set_outfile_redirection(list->rdr_out);
	close(list->end[0]);
	close(list->end[1]);
}
