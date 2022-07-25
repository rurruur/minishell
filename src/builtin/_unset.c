/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _unset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:36:53 by jrim              #+#    #+#             */
/*   Updated: 2022/07/25 10:25:53 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	msh_unset(t_token *argv, t_env *envlst);
int		_unset_valid(char *str);
void	_unset_env(char *key, t_env *envlst);

void	msh_unset(t_token *argv, t_env *envlst)
{
	argv = argv->next;
	while (argv)
	{
		if (_unset_valid(argv->str) == VALID)
			_unset_env(argv->str, envlst);
		else
		{
			ft_putstr_fd("gumshell: unset: `", STDERR_FILENO);
			ft_putstr_fd(argv->str, STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			g_status = 1;
		}
		argv = argv->next;
	}
}

int	_unset_valid(char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
		return (INVALID);
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (INVALID);
		str++;
	}
	return (VALID);
}

void	_unset_env(char *key, t_env *envlst)
{
	while (envlst)
	{
		if (ft_strcmp(envlst->key, key) == 0)
			break ;
		envlst = envlst->next;
	}
	if (envlst)
		del_from_envlst(&envlst);
}
