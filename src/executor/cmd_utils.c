/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 23:06:23 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/14 23:06:58 by nakkim           ###   ########.fr       */
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
	arr[count] = NULL;
	count = 0;
	while (cmds)
	{
		arr[count++] = ft_strdup(cmds->str);
		cmds = cmds->next;
	}
	return (arr);
}

char	*double_strjoin(char *start, char *middle, char *end)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(start, middle);
	result = ft_strjoin(tmp, end);
	free(tmp);
	return (result);
}

void	destroy_split(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

char	*get_valid_cmd_path(char *cmd)
{
	struct stat	stat_result;
	char		*cmd_path;
	char		**path;
	int			i;
	
	path = ft_split(getenv("PATH"), ':');	// free?
	i = -1;
	while (path[++i])
	{
		cmd_path = double_strjoin(path[i], "/", cmd);
		if (stat(cmd_path, &stat_result) != -1)
			break ;
		free(cmd_path);
	}
	destroy_split(path);
	if (!path[i]) {	// 여기 에러 처리 좀 더 고민
		return (0);
	}
	return (cmd_path);
}