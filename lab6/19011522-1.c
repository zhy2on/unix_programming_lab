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

void do_child(int fd){
	char buf[5]={0};
	// 파일에서 문자 2개 읽어 자신의 process id와 함께 출력
	read(fd, buf, 2);
	printf("pid=%d ... %s ...\n", getpid(), buf);
	exit(0); // 이 부분의 코드는 변경 금지
}

int main(int ac, char **av) {	
	int num, i, fd;
	pid_t pid;
	if (ac != 3)
		return ;

	// main 함수의 인자로 주어진 파일 open
	fd = open(av[1], O_RDONLY);
	// main 함수의 인자를 정수로 변환
	num = atoi(av[2]);
	for (i=0; i<num; i++){
		// child process 생성
		if (fork() == 0){
			do_child(fd);
		}
	}
	for (i=0; i<num; i++){ // 이 부분의 코드는 변경 금지
		wait(0);
	}
	return 0;
}
