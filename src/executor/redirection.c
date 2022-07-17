/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 23:05:18 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/17 13:37:34 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_infile_redirection(t_token *files)
{
	int	fd;
	int	result;

	while (files)
	{
		fd = open(files->str, O_RDONLY);
		if (fd < 0)
			return (0);
		if (files->next == NULL)
			break ;
		close(fd);
		files = files->next;
	}
	result = dup2(fd, STDIN_FILENO);
	if (result < 0)
		return (-1);
	close(fd);
	return (1);

}

int	set_outfile_redirection(t_toklst *list)
{
	int	fd;
	int	result;
	t_token	*files;

	files = list->rdr_out;
	while (files)
	{
		if (files->type == T_RDR_OUT)
			fd = open(files->str, O_WRONLY | O_TRUNC | O_CREAT, 0777);
		else if (files->type == T_RDR_AP)
			fd = open(files->str, O_WRONLY | O_APPEND | O_CREAT, 0777);
		if (fd < 0)
			return (0);
		if (files->next == NULL)
			break ;
		close(fd);
		files = files->next;
	}
	result = dup2(fd, STDOUT_FILENO);
	if (result < 0)
		return (-1);
	close(fd);
	return (1);
}

void	set_redirection(t_toklst *list, int prev_end)
{
	int	result;

	// if (list->end[0] != -1)
	// 	close(list->end[0]);
	if (prev_end != -1)
	{
		dup2(prev_end, STDIN_FILENO);
		dprintf(g_fd, "prev_end(%d)을 STDIN으로 설정\n", prev_end);
	}
	if (list->rdr_in)
	{
		// STDIN 설정
		result = set_infile_redirection(list->rdr_in);
		if (result == 0)
			perror("redirection error");	// infile 하나라도 없는 경우: 해당 노드는 실행 x
		else if (result == -1)
			perror("dup2");		// 어캐 해야? 걍 종료?
	}
	if (list->rdr_out)
	{
		// STDOUT 설정
		result = set_outfile_redirection(list);
		if (result == 0)
			perror("open error");	// outfile open error: 어캐 처리??
		else if (result == -1)
			perror("dup2");
	}
	else if (list->next != NULL)	// out redirection 없고, 마지막 명령어가 아닐 경우 파이프로 표준출력
	{
		if (dup2(list->end[1], STDOUT_FILENO) < 0)
			perror("dup2");
		dprintf(g_fd, "list->end[1]을 STDOUT으로 설정\n");
	}
	dprintf(g_fd, "rdr set done(pid: %d)\n", getpid());
}
