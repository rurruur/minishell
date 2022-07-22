/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 11:58:02 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/23 00:02:05 by nakkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*make_file_name(char *heredoc)
{
	char		*file_name;
	char		*new_name;
	struct stat	info;

	file_name = ft_strjoin("/tmp/", heredoc);
	if (!file_name)
		ft_error("malloc");
	while (!stat(file_name, &info))
	{
		new_name = ft_strjoin(file_name, "_");
		if (!new_name)
			ft_error("malloc");
		free(file_name);
		file_name = new_name;
	}
	return (file_name);
}

int	process_heredoc(t_token *heredoc_tok, char *filename)
{
	char	*line;
	int		fd;

	handle_sig(HEREDOC);
	fd = open(filename, O_WRONLY | O_CREAT, 0777);
	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(heredoc_tok->str, line))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	exit(0);
}

static int	check_cmd_heredoc(t_token *rdr_in)
{
	int		child;
	char	*filename;

	while (rdr_in)
	{
		if (rdr_in->type == T_RDR_HD)
		{
			filename = make_file_name(rdr_in->str);
			child = fork();
			if (child == 0)
				process_heredoc(rdr_in, filename);
			handle_sig(SIG_WAIT);
			free(rdr_in->str);
			rdr_in->str = filename;
			wait(&g_status);
			handle_sig(READLINE);
			if (WEXITSTATUS(g_status) == 1)
			{
				g_status = WEXITSTATUS(g_status);
				return (0);
			}
		}
		rdr_in = rdr_in->next;
	}
	return (1);
}

int	check_heredoc(t_toklst *list)
{
	g_status = 0;
	while (list)
	{
		if (!check_cmd_heredoc(list->rdr_in))
			return (0);
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
