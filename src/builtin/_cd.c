/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:35:52 by jrim              #+#    #+#             */
/*   Updated: 2022/07/17 20:32:33 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#define MAX_PATH_LEN 4096

void	_pwd_(void)
{
	char	*pwd;
	char	buf[MAX_PATH_LEN];

	pwd = getcwd(buf, MAX_PATH_LEN);
	printf("pwd : %s\n", pwd);
}

void	_cd_home(char *path, t_env *envlst)
{
	path = get_env_val(envlst, "HOME");
	printf("(home) path : %s\n", path);
	if (chdir(path) == -1)
		printf("HOME is not set\n");
	_pwd_();
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
	else										// cd 어쩌구
	{
		// type 확인해서 환경변수면 앞에서부터 올바른 경로만 잘라?
		if (chdir(path) == -1)
			printf("minishell: cd: %s: No such file or directory\n", path); // 임시 error msg
		// envlst 새로 setting
		_pwd_();
	}
	return (1);
}