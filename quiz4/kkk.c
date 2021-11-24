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

void catchsig(int);

void do_child(void){
	int i, in, fd;
	// “data1” 파일을 쓰기 가능하게 open
	while ((fd =  open("data1", O_WRONLY) > 0))
		;
	for (i=0; i<5; i++){
		scanf("%d", &in);
		// “data1” 파일에 정수를 하나 쓰기
		write(fd, &in, sizeof(int));
		printf("child writes %d\n", in);
		sleep(1);
		// parent에게 SIGUSR1 signal 보내기
		kill(getpgid(0), SIGUSR1);
		sleep(1);
	}
	exit(0);
}

int main(void) {	
	int i, in, fd, status;
	pid_t pid;
	static struct sigaction act;
	
	// SIGUSR1 signal 처리 설정
	act.sa_handler = catchsig;
	sigaction(SIGUSR1, &act, NULL);

	if ((pid=fork())==0){
		do_child();
	}
	// “data1” 파일을 읽기 가능하게 open
	fd = open("data1", O_RDONLY|O_CREAT, 0600);
	for(i=0; i<5; i++){
		// child의 signal을 받고, “data1” 파일에서 정수를 하나 읽기
		pause();
		read(fd, &in, sizeof(int));
		printf("parent reads %d\n", in);
	}
	wait(&status);
	exit(0);
}

void catchsig(int signo) {
}
