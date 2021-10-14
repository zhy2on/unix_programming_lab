#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <ftw.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <time.h>

int main(void) {	
	int i, status;
	pid_t pid[3];
	pid_t p;

	for (i=0; i<3; i++){
		// child process 생성
		pid[i] = fork();
		if (pid[i] == 0) {
			if (i == 0){
				// 첫 번째 child가 새로운 프로그램 실행 시작
				execl("./19011522-1-a", "./19011522-1-a", "abc", (char *)0);
				exit(0);
			}
			else if (i == 1){
				// 두 번째 child가 새로운 프로그램 실행 시작
				execl("./19011522-1-b", "./19011522-1-b", (char *)0);
				exit(0);
			}
			else if (i == 2){
				// 세 번째 child가 새로운 프로그램 실행 시작
				execl("./19011522-1-c", "./19011522-1-c", (char *)0);
				exit(0);
			}
		}
	}
	for (i=2; i>= 0; i--){
		// 세 child의 종료 상태를 종료 순서대로 확인 & 출력
		p = waitpid(pid[i], &status, 0);
		printf("pid=%ld ... exit=%d\n", p, WEXITSTATUS(status));
	}
	exit(0);
}
