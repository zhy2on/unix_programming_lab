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

void do_child(int i){
	int j;
	static struct sigaction act;
	// SIGUSR1 signal 처리가 가능 하도록 설정
	act.sa_handler = catchsig;
	sigaction(SIGUSR1, &act, NULL);
	pause();
	// signal을 받으면, process id 세 번 출력 하도록 설정
	for (j = 0; j < 3; j++) {
		printf("cid=%d\n", getpid());
	}
	exit(i);
}

int main(void) {	
	int i, cid, status;
	pid_t pid[3];
	for (i=0;i<3;i++){
		pid[i]=fork();
		if (pid[i]==0) {
			do_child(i);
		}
	}
	// 1초씩 sleep()하면서, child들에게 SIGUSR1 signal 보내기
	for (i = 0; i < 3; i++) {
		kill(pid[i], SIGUSR1);
		sleep(1);
	}
	for (i=0;i<3;i++){
		cid=wait(&status);
		printf("child id=%d, exit status=%d\n", cid, WEXITSTATUS(status));
	}
	exit(0);
}
