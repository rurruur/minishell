/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 23:03:49 by nakkim            #+#    #+#             */
/*   Updated: 2022/07/17 12:00:24 by nakkim           ###   ########.fr       */
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

void	child_process(t_toklst *list, int prev_end, t_env *envlst)
{
	char	*cmd;
	char	**cmd_arr;
	char	**env;

	set_redirection(list, prev_end);
	if (list->cmd)
	{
		if (is_builtin(list->cmd->str))
		{
			if (builtin_main(list->cmd->str, list->cmd, envlst))
				exit(1);
			// free는해야돼..
		}
		cmd = get_valid_cmd_path(list->cmd->str, envlst);
		if (!cmd) {
			// cmd 못찾은 경우
			perror("command");
			exit(1);
		} else {
			// cmd free 필요
			cmd_arr = list_to_arr(list->cmd);	// 각각 free 필요?
			dprintf(g_fd, "cmd execute(pid: %d)\n", getpid());
			env = get_env(envlst);
			if (!execve(cmd, cmd_arr, env))
			{
				perror("execve");
				free(cmd);
				// env free
				destroy_split(cmd_arr);
			}
		}
	}
	exit(1);
}

void	parent_process(pid_t child, int *end)
{
	int		status;

	close(end[1]);	// 에러??
	if (dup2(end[0], STDIN_FILENO) < 0)
		perror("dup2");
	waitpid(child, &status, 0);
}

void	print_list(t_toklst *list)
{
	t_token	*tmp;
	
		dprintf(g_fd, "\n========node(%p)=======\n", list);
		dprintf(g_fd, "cmd: ");
		tmp = list->cmd;
		while(tmp)
		{
			dprintf(g_fd, "%s ", tmp->str);
			tmp = tmp->next;
		}
		dprintf(g_fd, "\nnext: %p\n", list->next);
		
		dprintf(g_fd, "===================================\n");
}

void	executor(t_toklst *list, t_env *envlst)
{
	int		prev_end;
	pid_t	child;

	prev_end = -1;
	while (list != NULL)
	{
		list->end[0] = -1;
		list->end[1] = -1;
		print_list(list);
		dprintf(g_fd, "\n= executor(%d) =\n", getpid());
		if (list->next != NULL && pipe(list->end) == -1)	// 다음 노드가 있을 경우 파이프 생성
		{
			perror("pipe");
			return ;	// 리턴할지 아니면 다음 명령어로 넘어갈지 결정
		}
		child = fork();
		dprintf(g_fd, "fork: %d\n", getpid());
		if (child == -1)
		{
			perror("fork");
			return ;
		}
		if (child == 0)
			child_process(list, prev_end, envlst);
		// else
		// 	parent_process(child, end);
		else
		{
			wait(&child);
			close(list->end[1]);
			close(prev_end);
		}
		if (list->end[0] != -1)
		{
			prev_end = dup(list->end[0]);
			// dup2(prev_end, list->end[0]);
			// prev_end = list->end[0];
			// dprintf(g_fd, "prev_end: %d\tcurr_end: %d, %d\n", prev_end, list->end[0], list->end[1]);
			dprintf(g_fd, "set prev\n");
		}
		list = list->next;
	}
}
