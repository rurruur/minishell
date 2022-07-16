/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:36:53 by jrim              #+#    #+#             */
/*   Updated: 2022/07/17 03:14:02 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// 환경변수 이름 규칙
// 1. a~z, A~Z, _, 0~9
// 2. 단 숫자로 시작할 수 없다.

int	_unset_valid_key(char *str)
{
	if (ft_isdigit(*str))
		return (0);
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

int _unset_is_key(char *key, t_env *envlst)
{
	int	cnt;

	cnt = 1;
	while (envlst)
	{
		if (ft_strncmp(envlst->key, key, ft_strlen(key)) == 0)
			return (cnt);
		cnt++;
		envlst = envlst->next;
	}
	if (!envlst)
		cnt = 0;
	return (cnt);
}

void	_unset_env(char *key, t_env *envlst)
{
	int		cnt;
	t_env	*tmp;

	cnt = _unset_is_key(key, envlst);
	if (cnt == 0)
		return ;
	else if (cnt == 1)				//제일 첫 노드
	{
		tmp = envlst;
		envlst = envlst->next;
		free(tmp->key);
		free(tmp->val);
		tmp->next = NULL;
	}
	while (cnt-- > 1)
		envlst = envlst->next;
	if (envlst->next->next == NULL)	//제일 끝 노드
	{
		tmp = envlst->next;
		envlst->next = NULL;
		free(tmp->key);
		free(tmp->val);
		tmp->next = NULL;
	}
	else
	{
		tmp = envlst->next;
		envlst->next = envlst->next->next;
		free(tmp->key);
		free(tmp->val);
		tmp->next = NULL;
	}
}

int	msh_unset(t_token *argv, t_env *envlst)
{
	// if (argv || envlst)
	// 	printf("unset 아직 안만들었단다\n");
	argv = argv->next;
	while (argv)
	{
		if (_unset_valid_key(argv->str))
			_unset_env(argv->str, envlst);
		argv = argv->next;
	}
	return (1);
}