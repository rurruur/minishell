/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 11:58:02 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/19 21:58:46 by nakkim           ###   ########.fr       */
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

void	process_heredoc(t_token *heredoc_tok, char *filename)
{
	char	*line;
	int		fd;
	int		line_len;

	handle_sig(HEREDOC);
	fd = open(filename, O_WRONLY | O_CREAT, 0777);
	while (1)
	{
		line = readline("> ");
		line_len = ft_strlen(line);
		if (!ft_strncmp(heredoc_tok->str, line, line_len))
		{
			free(line);
			break ;
		}
		write(fd, line, line_len);
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	exit(0);
}

static int	heredoc_wait(void)
{
	g_status = 0;
	wait(&g_status);
	if (WEXITSTATUS(g_status) != 0)
		return (0);
	return (1);
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
				if (!heredoc_wait())
				{
					while (list)
					{
						if (list->rdr_in->type == T_RDR_HD)
						{
							unlink(filename);
							dprintf(g_fd, "delete %s(because of heredoc err)\n", filename);
						}
						list = list->prev;
					}
					// clear toklst 전에 clean heredoc 만들어서 stat으로 확인 후 지우기
					return (0);
				}
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