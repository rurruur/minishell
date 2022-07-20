/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _export.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:36:53 by jrim              #+#    #+#             */
/*   Updated: 2022/07/20 13:31:32 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		msh_export(t_token *argv, t_env *envlst);
int		_export_valid(char *str);
void	_export_display(t_env *envlst);

static void	error(char *err_msg)
{
	ft_putstr_fd("( ༎ຶД༎ຶ): ", STDERR_FILENO);
	ft_putstr_fd(err_msg, STDERR_FILENO);
	ft_putendl_fd(": not a valid identifier", STDERR_FILENO);
	exit (1);
}

int	msh_export(t_token *argv, t_env *envlst)
{
	int		key_len;
	char	*env_key;
	char	*env_val;

	if (argv->next == NULL)
		_export_display(envlst);
	argv = argv->next;
	while (argv)
	{
		key_len = _export_valid(argv->str);
		if (key_len)
		{
			env_key = ft_strndup(argv->str, key_len);
			env_val = ft_strdup(argv->str + key_len + 1);
			if (get_env_val(envlst, env_key))
				change_env_val(envlst, env_key, env_val);
			else
				add_to_envlst(&envlst, init_envlst(env_key, env_val));
		}
		else
			error(double_strjoin("export: `", argv->str, "'"));
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
	if (str[idx] == '=')
		return (idx);
	else
		return (0);
}

void	_export_display(t_env *envlst)
{
	while (envlst)
	{
		printf("declare -x ");
		printf("%s=\"%s\"\n", envlst->key, envlst->val);
		envlst = envlst->next;
	}
}
