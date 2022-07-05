
	// fork
	child = fork();
	if (child == -1)
		perror("fork: ");
	else if (child == 0) {
		// child process
		puts("\t---child---");

		int	infile_fd = open(first.node.infile, O_RDONLY);
		printf("file open: %d\n", infile_fd);
		if (infile_fd < 0)
			perror("file open error");

		close(end[0]);

		// stdin, stdout 연결
		if (dup2(infile_fd, STDIN_FILENO) < 0)
			perror("dup2");
		if (dup2(end[1], STDOUT_FILENO) < 0)
			perror("dup2");

		// 명령어 경로 찾기
		if (!first.node.cmd[0])  // 반복문으로 변경??
			exit(1);
		char	*cmd = get_cmd_path(first.node.cmd, path);
		if (!cmd)
			perror("Cannot find cmd path");

		// 명령 실행
		char *cmd_line[] = { first.node.cmd, first.node.param[0], NULL };
		execve(cmd, cmd_line, env);
		perror("execve");
	}
	else
	{
		close(end[1]);
		dup2(end[0], STDIN_FILENO);
		puts("wait - parent");
		waitpid(child, &exit_status, 0);

		// 명령어 경로 찾기
		char	*cmd = get_cmd_path(second.node.cmd, path);
		if (!cmd)
			perror("Cannot find cmd path");

		// 명령 실행
		// char *cmd_line[] = { second.node.cmd, second.node.param[0], NULL };
		// execve(cmd, cmd_line, env);

		close(end[0]);
		puts("\t---parent---");
		puts("done - parent");
	}