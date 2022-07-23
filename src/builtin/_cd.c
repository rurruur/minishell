/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:35:52 by jrim              #+#    #+#             */
/*   Updated: 2022/07/23 16:03:27 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		msh_cd(t_token *argv, t_env *envlst);
int		_cd_move(t_token *argv, t_env *envlst);
void	_cd_error(char *str, int type);
int		_cd_env(char *str, t_env *envlst);
int		_cd_str(char *err_msg, int type);

int	msh_cd(t_token *argv, t_env *envlst)
{
	char	*old_pwd;

	old_pwd = getcwd(0, MAX_PATH_LEN);
	if (_cd_move(argv, envlst))
		free(old_pwd);
	else
	{
		change_env_val(envlst, "OLDPWD", old_pwd);
		change_env_val(envlst, "PWD", getcwd(0, MAX_PATH_LEN));
	}
	return (1);
}

int	_cd_move(t_token *argv, t_env *envlst)
{
	char	*str;
	int		type;
	int		flag;

	flag = 0;
	if (argv->next == NULL)
	{
		flag = _cd_env(NULL, envlst);
		return (flag);
	}
	str = argv->next->str;
	type = argv->next->type;
	if (ft_strchr("~-", str[0]) && str[1] == '\0')
		flag = _cd_env(str, envlst);
	else if (ft_strcmp(str, "--") == 0)
		flag = _cd_env(NULL, envlst);
	else if (type == T_ENV && str[0] == '\0')
		flag = _cd_env(NULL, envlst);
	else if (type == T_ENV && str[0] != '\0')
		flag = _cd_str(str, type);
	else if (type == T_OFF)
		flag = _cd_str(str, type);
	return (flag);
}

void	_cd_error(char *err_msg, int type)
{
	ft_putstr_fd("( ༎ຶД༎ຶ): cd: ", STDERR_FILENO);
	ft_putstr_fd(err_msg, STDERR_FILENO);
	if (type == 1)
		ft_putendl_fd(" not set", STDERR_FILENO);
	else if (type == 2)
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	else if (type == 3)
		ft_putendl_fd(": Not a directory", STDERR_FILENO);
	g_status = 1;
}

int	_cd_env(char *str, t_env *envlst)
{
	char	*path;
	char	*err_msg;

	if (str == NULL || (str[0] == '~' && str[1] == '\0'))
	{
		path = get_env_val(envlst, "HOME");
		err_msg = msh_strdup("HOME");
	}
	else
	{
		path = get_env_val(envlst, "OLDPWD");
		err_msg = msh_strdup("OLDPWD");
	}
	if (path && chdir(path) != -1)
	{
		if (str && str[0] == '-' && str[1] == '\0')
			printf("%s\n", path);
		g_status = 0;
		free(path);
	}
	else
		_cd_error(err_msg, 1);
	free(err_msg);
	return (g_status);
}

int	_cd_str(char *str, int type)
{
	char		*path;
	struct stat	stat_result;

	path = NULL;
	if (type == T_OFF)
		path = msh_strdup(str);
	else if (type == T_ENV)
		path = msh_strdup(str);
	if (chdir(path) == -1)
	{
		if (stat(path, &stat_result) != -1 && stat_result.st_mode != 0040000)
			_cd_error(path, 3);
		else
			_cd_error(path, 2);
	}
	else
		g_status = 0;
	free(path);
	return (g_status);
}
