/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:35:52 by jrim              #+#    #+#             */
/*   Updated: 2022/07/17 18:11:58 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// cd $adf 가 문제인 상황 수정필요

// 있는 경로일 때는 이동하고
// 없는 경로일 때는 No such file or directory
// 인자가 여러개 들어와도 맨 앞 하나의 인자만 사용

void	_cd_home(char *path, t_env *envlst)
{
	path = get_env_val(envlst, "HOME");
	printf("(home) path : %s\n", path);
	if (chdir(path) == -1)
		printf("HOME is not set\n");
}

void	_cd_env(char *path, t_env *envlst)
{
	if (path[0] == '$' && path[1] == '\0')
	{
		printf("minishell: cd: $: No such file or directory\n"); // 임시 error msg
		return ;
	}
	path = get_env_val(envlst, path + 1);
	printf("(env) path : %s\n", path);
	if (chdir(path) == -1)
		chdir(get_env_val(envlst, "HOME"));
}

// void	_cd_get_path(char *path)
// {
	
// }

int	msh_cd(t_token *argv, t_env *envlst)
{
	char	*path;
	
	path = NULL;
	if (argv->next)
		path = argv->next->str;
	if (argv->next == NULL)						// 그냥 cd
		_cd_home(path, envlst);
	else if (path[0] == '~' && path[1] == '\0')	// cd ~
		_cd_home(path, envlst);
	else if (path[0] == '$')					// cd $어쩌구
		_cd_env(path, envlst);
	else										// cd 어쩌구
	{
		if (chdir(path) == -1)
			printf("minishell: cd: %s: No such file or directory\n", path); // 임시 error msg
		printf("(dfl) path : %s\n", path);
		// envlst 새로 setting
	}
	return (1);
}