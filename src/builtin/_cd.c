/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:35:52 by jrim              #+#    #+#             */
/*   Updated: 2022/07/18 17:39:39 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#define MAX_PATH_LEN 4096

int		msh_cd(t_token *argv, t_env *envlst);
void	_pwd_(void); // 나중에 지워라
char	*_cd_get_path(t_token *argv, t_env *envlst);
void	_cd_env(char *path, t_env *envlst);

int	msh_cd(t_token *argv, t_env *envlst)
{
	char	*path;
	
	path = NULL;
	if (argv->next == NULL)						// cd
		path = get_env_val(envlst, "HOME");
	else
	{
		argv = argv->next;
		path = _cd_get_path(argv, envlst);
	}
	if (chdir(path) == -1)
		printf("minishell: cd: %s: No such file or directory\n", path);
	free(path);
	// envlst 새로 setting ?
	return (1);
}

void	_pwd_(void)
{
	char	*pwd;
	char	buf[MAX_PATH_LEN];

	pwd = getcwd(buf, MAX_PATH_LEN);
	printf("pwd : %s\n", pwd);
}

char	*_cd_get_path(t_token *argv, t_env *envlst)
{
	char	*path;
	char	*str;
	int		type;

	path = NULL;
	str = argv->str;
	type = argv->type;
	if (str[0] == '~' && str[1] == '\0')	// cd ~
		path = get_env_val(envlst, "HOME");
	else if (type == T_OFF)
		path = ft_strdup(str);
	else if (type == T_ENV)
		;
	return (path);
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
