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

void do_child(void){
	// process id, group id, session id 출력
	printf("pid=%ld ... gid=%ld ... sid=%ld\n", getpid(), getpgid(0), getsid(0));
	exit(0);
}

int main(int argc, char **argv) {	
	int num, i;
	pid_t pid;
	// main 함수의 인자를 정수로 변환
	num = atoi(argv[1]);
	for (i=0; i<num; i++){
		// child process 생성
		pid = fork();
		if (pid == 0){
			do_child();
		}
	}
	for (i=0; i<num; i++){ // 이 부분의 코드는 변경 금지
		wait(0);
	}
	return 0;
}
