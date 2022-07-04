#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

// fd[0] : read		-> 부모 프로세스에게는 필요하지 않음
// fd[1] : write	-> 자식 프로세스에게는 필요하지 않음

int main(int argc, char *argv[]) 
{
	int 	fds[2];					// 2개의 fd를 담을 배열을 정의한다.
	pipe(fds);                      // pipe를 호출해 두 개의 fd로 배열을 채워준다.
	pid_t	pid = fork();           // 부모 프로세스의 fd와 메모리를 복제한 자식 프로세스 생성한다.

	if (pid == 0) 								// if pid == 0, 자식 프로세스
	{   
		printf("child process running...");               
		close(fds[1]);               			// 자식 프로세스는 write가 필요 없으므로 닫아준다.
		dup2(fds[0], STDIN_FILENO);    			// fds[0]으로 표준입력을 넘겨준다.
		close(fds[0]);                			// fds[0]은 자식 프로세스에서 더이상 필요하지 않기 떄문에 닫아준다. 복사본이기 때문에(?)
		char *cmd[] = {(char *)"sort", NULL};   // sort 명령어 인자를 만들어준다.
		if (execvp(cmd[0], cmd) < 0) 
		printf("child process terminated...");               
		exit(0); 								// sort 명령어 실행하고 문제있으면 exit
	} 
	// 부모 프로세스 코드 시작
	printf("parent process running...");               
	close(fds[0]);                 				// 부모 프로세스는 read가 필요 없으므로 닫아준다. 
	const char *words[] = {"c", "b", "a"}; 		// 자식 프로세스에서 읽을 write input 

	for (int i = 0; i < 3; i++)
		dprintf(fds[1], "%s\n", words[i]); 		// fds[1]에 출력을 쓴다.
	close(fds[1]); 

	int 	status;
	pid_t	wpid = waitpid(pid, &status, 0); 		// 자식 프로세스가 종료될때까지 기다린다.
	return (wpid == pid && WIFEXITED(status) ? WEXITSTATUS(status) : -1);
}