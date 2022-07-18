/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakkim <nakkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 23:03:49 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/18 17:05:30 by nakkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *cmd)
{
	int	cmd_len;

	cmd_len = ft_strlen(cmd);
	// 옵션 같은 경우는 어떻게..? 옵션 있으면 구현 해야하는 거인지 확인 하고 맞으면 빌트인?
	// 예를 들면 echo -n 은 빌트인으로 처리하는데
	// echo -e는 execve로 실행햐야 하는 거 아냐
	if (ft_strncmp("exit", cmd, cmd_len) || ft_strncmp("echo", cmd, cmd_len)
		|| ft_strncmp("cd", cmd, cmd_len) || ft_strncmp("pwd", cmd, cmd_len)
		|| ft_strncmp("export", cmd, cmd_len)
		|| ft_strncmp("unset", cmd, cmd_len) || ft_strncmp("env", cmd, cmd_len))
		return (1);
	return (0);
}

void	child_process(t_toklst *list, t_env *envlst)
{
	char	*cmd;
	char	**cmd_arr;
	char	**env;

	set_redirection(list);
	// if (is_builtin(list->cmd->str))
	// {
	// 	if (builtin_main(list->cmd->str, list->cmd, envlst))
	// 		exit(0);
	// 	// free는해야돼..
	// }
	cmd = get_valid_cmd_path(list->cmd->str, envlst);
	cmd_arr = list_to_arr(list->cmd);
	env = get_env(envlst);
	close(list->end[0]);
	close(list->end[1]);
	if (execve(cmd, cmd_arr, env) == -1)
	{
		free(cmd);
		destroy_split(cmd_arr);
		destroy_split(env);
		ft_error(list->cmd->str);
	}
}

void	executor(t_toklst *list, t_env *envlst)
{
	t_toklst	*tmp;
	pid_t	child;

	tmp = list;
	while (list)
	{
		if (pipe(list->end) == -1)
			ft_error("pipe");
		child = fork();
		if (child == -1)
			ft_error("fork");
		if (child == 0)
			child_process(list, envlst);
		close(list->end[1]);
		list = list->next;
	}
	ft_wait();
	while (tmp)
	{
		close(tmp->end[0]);
		tmp = tmp->next;
	}
}
