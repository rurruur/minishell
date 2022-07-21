/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:35:52 by jrim              #+#    #+#             */
/*   Updated: 2022/07/21 18:31:15 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#define MAX_PATH_LEN 4096

// cd ""
// cd -

int		msh_cd(t_token *argv, t_env *envlst);
void	_cd_set_oldpwd(t_env *envlst);
char	*_cd_get_path(t_token *argv, t_env *envlst);

int	msh_cd(t_token *argv, t_env *envlst)
{
	char	*old_pwd;
	char	*path;

	old_pwd = get_env_val(envlst, "OLDPWD");
	if (argv->next == NULL)
		path = get_env_val(envlst, "HOME");
	else
		path = _cd_get_path(argv->next, envlst);
	if (chdir(path) == -1)
	{
		errno = NO_EXIST;
		builtin_error(ft_strjoin("cd: ", path));
		free(old_pwd);
	}
	else
	{
		change_env_val(envlst, "OLDPWD", old_pwd);
		change_env_val(envlst, "PWD", getcwd(0, MAX_PATH_LEN));
	}
	free(path);
	return (1);
}

char	*_cd_get_path(t_token *argv, t_env *envlst)
{
	char	*path;
	char	*str;
	int		type;

	path = NULL;
	str = argv->str;
	type = argv->type;
	if (str[0] == '~' && str[1] == '\0')
		path = get_env_val(envlst, "HOME");
	else if (str[0] == '-' && str[1] == '\0')
		path = get_env_val(envlst, "OLDPWD");
	else if (type == T_OFF)
		path = ft_strdup(str);
	else if (type == T_ENV)
	{
		if (str[0] == '\0')
			path = get_env_val(envlst, "HOME");
		else
			path = ft_strdup(str);
	}
	return (path);
}
