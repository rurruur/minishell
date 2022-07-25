/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 17:24:38 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/23 18:48:36 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_infiles(t_token *files)
{
	struct stat	info;

	while (files)
	{
		if (stat(files->str, &info) == -1)
		{
			errno = NO_EXIST;
			ft_file_error(files->str);
			return (0);
		}
		if (files->next == NULL)
			break ;
		files = files->next;
	}
	return (1);
}

int	check_outfiles(t_token *files)
{
	int	fd;

	while (files)
	{
		if (files->type == T_RDR_OUT)
			fd = open(files->str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else if (files->type == T_RDR_AP)
			fd = open(files->str, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (fd < 0)
		{
			ft_file_error(files->str);
			return (0);
		}
		close(fd);
		if (files->next == NULL)
			break ;
		files = files->next;
	}
	return (1);
}

void	check_files(t_toklst *list)
{
	if (!check_infiles(list->rdr_in) || !check_outfiles(list->rdr_out))
		exit(1);
}

char	**get_env_path(t_env *env, char *cmd)
{
	char		*result;
	char		**path;

	result = get_env_val(env, "PATH");
	if (!result)
	{
		errno = CMD_NOT_FOUND;
		ft_error(cmd);
	}
	path = ft_split(result, ':');
	if (!path)
		ft_error("malloc");
	return (path);
}
