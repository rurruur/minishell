/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 11:58:02 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/17 12:55:21 by nakkim           ###   ########.fr       */
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

void	process_heredoc(t_token *heredoc_tok)
{
	char	*line;
	char	*file_name;
	int		fd;
	int		line_len;

	file_name = make_file_name(heredoc_tok->str);
	fd = open(file_name, O_WRONLY | O_CREAT, 0777);
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
	heredoc_tok->str = file_name;
}

void	check_heredoc(t_toklst *list)
{
	t_token	*infile;

	while (list)
	{
		infile = list->infile;
		while (infile)
		{
			if (infile->type == T_RDR_HD)
			{
				// heredoc 처리
				// 파일 생성 후 infile->str 나올 때까지 readline으로 입력받음
				// 입력 받는 동안 시그널 처리? (ctrl+d, ctrl+c)
				// 파일명 정해서 파일 생성 후 해당 파일명으로 infile->str 교체
				// executor 끝나면 파일 삭제 & 파일명 free
				process_heredoc(infile);
			}
			infile = infile->next;
		}
	}
}
