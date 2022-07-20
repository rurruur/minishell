/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 11:58:02 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/20 14:04:08 by jrim             ###   ########.fr       */
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

int	process_heredoc(t_token *heredoc_tok, char *filename)
{
	char	*line;
	int		fd;
	int		line_len;

	handle_sig(HEREDOC);
	dprintf(g_fd, "heredoc: %s #%s\n", heredoc_tok->str, filename);
	fd = open(filename, O_WRONLY | O_CREAT, 0777);
	while (1)
	{
		line = readline("> ");
		line_len = ft_strlen(line);
		if (line_len && !ft_strncmp(heredoc_tok->str, line, line_len))
		{
			free(line);
			dprintf(g_fd, "bye\n");
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	exit(1);
}

int	check_heredoc(t_toklst *list)
{
	t_token	*rdr_in;
	int		child;
	char	*filename;

	while (list)
	{
		rdr_in = list->rdr_in;
		while (rdr_in)
		{
			if (rdr_in->type == T_RDR_HD)
			{
				filename = make_file_name(rdr_in->str);
				child = fork();
				if (child == 0)
					process_heredoc(rdr_in, filename);
				handle_sig(WAIT_HEREDOC);
				wait(&g_status);
				handle_sig(READLINE);
				free(rdr_in->str);
				rdr_in->str = filename;
			}
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