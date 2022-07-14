/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 23:05:18 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/15 00:22:57 by jrim             ###   ########.fr       */
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
			fd = open(files->str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		else if (files->type == T_RDR_AP)
			fd = open(files->str, O_WRONLY | O_CREAT | O_APPEND, 0777);
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

void	set_redirection(t_toklst *list, int *end)
{
	int	result;

	if (list->infile)
	{
		// STDIN 설정
		result = set_infile_redirection(list->infile);
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
		close(end[0]);
		if (dup2(end[1], STDOUT_FILENO) < 0)
			perror("dup2");
	}
	// 	// STDIN 설정
	// if (list->infile && !set_file_redirection(list->infile, IN))
	// 	perror("redirection error");	// infile 하나라도 없는 경우: 해당 노드는 실행 x
	// // STDOUT 설정
	// if (list->outfile && !set_file_redirection(list->outfile, OUT))
	// 	perror("redirection error");	// outfile open error: 어캐 처리??
	// else if (list->next != NULL)	// out redirection 없고, 마지막 명령어가 아닐 경우 파이프로 표준출력
	// {
	// 	close(end[0]);
	// 	if (dup2(end[1], STDOUT_FILENO) < 0)
	// 		perror("dup2");
	// }
}
