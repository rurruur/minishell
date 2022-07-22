/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _export.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:36:53 by jrim              #+#    #+#             */
/*   Updated: 2022/07/23 01:09:36 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		msh_export(t_token *argv, t_env *envlst);
int		_export_valid(char *str);
void	_export_add(char *str, int key_len, t_env *envlst);
void	_export_error(char *err_msg);
void	_export_display(t_env *envlst);

int	msh_export(t_token *argv, t_env *envlst)
{
	int		key_len;

	if (argv->next == NULL)
		_export_display(envlst);
	argv = argv->next;
	while (argv)
	{
		key_len = _export_valid(argv->str);
		if (key_len != 0)
			_export_add(argv->str, key_len, envlst);
		else if (key_len == 0)
			_export_error(argv->str);
		argv = argv->next;
	}
	return (1);
}

int	_export_valid(char *str)
{
	int	idx;

	idx = 0;
	if (ft_isdigit(str[idx]))
		return (0);
	while (str[idx] != '\0' && str[idx] != '=')
	{
		if (!ft_isalnum(str[idx]) && str[idx] != '_')
			return (0);
		idx++;
	}
	return (idx);
}

void	_export_add(char *str, int key_len, t_env *envlst)
{
	char	*env_key;
	char	*env_val;

	env_key = ft_strndup(str, key_len);
	if (str[key_len] != '\0')
		env_val = ft_strdup(str + key_len + 1);
	else
		env_val = NULL;
	if (env_val == NULL || !find_env_val(envlst, env_key))
		add_to_envlst(&envlst, init_envlst(env_key, env_val));
	else
	{
		change_env_val(envlst, env_key, env_val);
		free(env_key);
	}
}

void	_export_display(t_env *envlst)
{
	while (envlst)
	{
		printf("declare -x %s", envlst->key);
		if (envlst->val)
			printf("=\"%s\"", envlst->val);
		printf("\n");
		envlst = envlst->next;
	}
}

void	_export_error(char *err_msg)
{
	ft_putstr_fd("( ༎ຶД༎ຶ): export: `", STDERR_FILENO);
	ft_putstr_fd(err_msg, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	g_status = 1;
}
