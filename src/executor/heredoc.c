/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 11:58:02 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/19 22:49:31 by nakkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*make_file_name(char *heredoc)
{
	char		*file_name;
	char		*new_name;
	struct stat	info;

	file_name = ft_strjoin("/tmp/", heredoc);
	while (!stat(file_name, &info))
	{
		new_name = ft_strjoin(file_name, "_");
		free(file_name);
		file_name = new_name;
	}
	return (file_name);
}

int	process_heredoc(t_token *heredoc_tok)
{
	char	*line;
	int		fd;
	int		line_len;
	char	*filename;

	handle_sig(HEREDOC);
	filename = make_file_name(heredoc_tok->str);
	dprintf(g_fd, "heredoc: %s #%s\n", heredoc_tok->str, filename);
	fd = open(filename, O_WRONLY | O_CREAT, 0777);
	while (1)
	{
		line = readline("> ");
		line_len = ft_strlen(line);
		if (!ft_strncmp(heredoc_tok->str, line, line_len))
		{
			free(line);
			dprintf(g_fd, "bye\n");
			break ;
		}
		write(fd, line, line_len);
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	free(heredoc_tok->str);
	heredoc_tok->str = filename;
	return (1);
}

int	check_heredoc(t_toklst *list)
{
	t_token	*rdr_in;

	while (list)
	{
		rdr_in = list->rdr_in;
		while (rdr_in)
		{
			if (rdr_in->type == T_RDR_HD && !process_heredoc(rdr_in))
				return (0);
			rdr_in = rdr_in->next;
		}
		list = list->next;
	}
	return (1);
}

void	clear_heredoc(t_toklst *list)
{
	t_token	*rdr_in;

	while (list)
	{
		rdr_in = list->rdr_in;
		while (rdr_in)
		{
			if (rdr_in->type == T_RDR_HD)
				unlink(rdr_in->str);
			rdr_in = rdr_in->next;
		}
		list = list->next;
	}
}