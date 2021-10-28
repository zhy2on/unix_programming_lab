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

void catchsig(int signo) {
	return ;
}

void do_child(int i, int *cid){
	int j;
	static struct sigaction act;
	pid_t pid;

	// SIGUSR1 signal 처리가 가능 하도록 설정
	act.sa_handler = catchsig;
	sigaction(SIGUSR1, &act, NULL);
	// 자신의 출력 순서가 될 때까지 대기
	if (i < 4)
		pause();
	pid=getpid();
	for (j=0;j<5;j++){
		printf("child %d .... \n", pid);
		sleep(1);
	}
	// 출력 완료 후 다음 출력 순서의 child에게 출력 시작을 알림
	if (i > 0)
		kill(cid[i-1], SIGUSR1);
	exit(0);
}

int main(void) {
	int i, status;
	pid_t pid[5];
	for (i=0;i<5;i++){
		pid[i]=fork();
		if (pid[i]==0) {
			do_child(i, pid);
		}
	}
	for (i=0;i<5;i++){
		wait(&status);
	}
	exit(0);
}
