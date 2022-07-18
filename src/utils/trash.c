// void	check_empty(t_token *pretok)
// {
// 	while (pretok)
// 	{
// 		if (pretok->str[0] == '\0')
// 		{
// 			del_from_strlst(&pretok);
// 		}
// 		else
// 			pretok = pretok->next;
// 	}
// }

// int	is_builtin(char *cmd)
// {
// 	int	cmd_len;

// 	cmd_len = ft_strlen(cmd);
// 	// 옵션 같은 경우는 어떻게..? 옵션 있으면 구현 해야하는 거인지 확인 하고 맞으면 빌트인?
// 	// 예를 들면 echo -n 은 빌트인으로 처리하는데
// 	// echo -e는 execve로 실행햐야 하는 거 아냐
// 	if (ft_strncmp("exit", cmd, cmd_len) || ft_strncmp("echo", cmd, cmd_len)
// 		|| ft_strncmp("cd", cmd, cmd_len) || ft_strncmp("pwd", cmd, cmd_len)
// 		|| ft_strncmp("export", cmd, cmd_len)
// 		|| ft_strncmp("unset", cmd, cmd_len) || ft_strncmp("env", cmd, cmd_len))
// 		return (1);
// 	return (0);
// }
