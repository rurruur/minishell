/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 23:06:23 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/25 10:18:36 by nakkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_cmd_count(t_token *cmds)
{
	int	size;

	size = 0;
	while (cmds)
	{
		cmds = cmds->next;
		size++;
	}
	return (size);
}

char	**list_to_arr(t_token *cmds)
{
	char	**arr;
	int		count;

	count = get_cmd_count(cmds);
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!arr)
		ft_error("malloc");
	arr[count] = NULL;
	count = 0;
	while (cmds)
	{
		arr[count] = ft_strdup(cmds->str);
		if (!arr[count])
			ft_error("malloc");
		count++;
		cmds = cmds->next;
	}
	return (arr);
}

void	destroy_split(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

static void	validate_path(char *path, struct stat stat_result, char *cmd)
{
	if (!path)
	{
		errno = CMD_NOT_FOUND;
		ft_error(cmd);
	}
	if (stat_result.st_mode == 0040000)
	{
		errno = IS_DIR;
		ft_error(cmd);
	}
}

void	get_valid_cmd_path(char *cmd, t_env *env, char **cmd_path)
{
	struct stat	stat_result;
	char		**path;
	int			i;

	if (ft_strrchr(cmd, '/'))
	{
		*cmd_path = cmd;
		return ;
	}
	path = get_env_path(env, cmd);
	i = -1;
	while (path[++i])
	{
		*cmd_path = double_strjoin(path[i], "/", cmd);
		if (!(*cmd_path))
			ft_error("malloc");
		if (stat(*cmd_path, &stat_result) != -1)
			break ;
		free(*cmd_path);
	}
	validate_path(path[i], stat_result, cmd);
	destroy_split(path);
}
