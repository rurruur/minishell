#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
	int fds[2];                      // 2개의 fd를 담을 배열을 정의한다.
	pipe(fds);                       // pipe를 호출해 두 개의 fd로 배열을 채워준다.

	int	fd = open("test", O_RDWR | O_CREAT | O_TRUNC);
	dprintf(fd, "file open\n");

	pid_t pid = fork();              // 부모 프로세스의 fd와 메모리를 복제한 자식 프로세스 생성한다.
	if (pid == 0) {                  // if pid == 0, 자식 프로세스
		// dup2(fds[0], STDIN_FILENO);    // fds[0]으로 표준입력을 넘겨준다.
		close(fds[0]);                 // fds[0]은 자식 프로세스에서 더이상 필요하지 않기 떄문에 닫아준다. 복사본이기 때문에(?)
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);                 // 원래부터 필요없었던 fd라 닫아준다.
		dprintf(fd, "child1\n");
		char *cmd[] = {(char *)"cat", "infile", NULL};   // sort 명령어 인자를 만들어준다.
		if (execvp(cmd[0], cmd) < 0) 
			exit(0);  // sort 명령어 실행하고 문제있으면 exit
	} 

	pid_t pid2 = fork();
	if (pid2 == 0) {                  // if pid == 0, 자식 프로세스
		dup2(fds[0], STDIN_FILENO);    // fds[0]으로 표준입력을 넘겨준다.
		close(fds[0]);                 // fds[0]은 자식 프로세스에서 더이상 필요하지 않기 떄문에 닫아준다. 복사본이기 때문에(?)
		// dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);                 // 원래부터 필요없었던 fd라 닫아준다.
		char *cmd[] = {(char *)"cat", NULL};   // sort 명령어 인자를 만들어준다.
		dprintf(fd, "child2\n");
		if (execvp(cmd[0], cmd) < 0) 
			exit(0);  // sort 명령어 실행하고 문제있으면 exit
	} 
	
	int status;
  // 부모 프로세스 코드 시작
	close(fds[1]);                 // 받기만 하면되는 부모 프로세스에서는 필요 없는 fd라 닫아준다. 
	close(fds[0]); 
	dprintf(fd, "wait start\n");	
	pid_t wpid = waitpid(pid, &status, 0); // 자식 프로세스가 종료될때까지 기다린다.
	pid_t wpid2 = waitpid(pid2, &status, 0); // 자식 프로세스가 종료될때까지 기다린다.
	dprintf(fd, "wait end\n");
	close(fd);
	return (wpid == pid && WIFEXITED(status) ? WEXITSTATUS(status) : -1);
}