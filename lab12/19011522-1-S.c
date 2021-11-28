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
	char f[6][3]={"f1", "f2", "f3", "f4", "f5", "f6"}; // 6개의 fifo 이름 정의
	char buf[512];
	int i, fd[6], n;
	fd_set set, master;
	int time;
	struct timeval t;

	for (i=0;i<6;i++){
		// 6개의 fifo 만들고, open
		mkfifo(f[i], 0600);
		fd[i] = open(f[i], O_RDWR);
	}
	
	// select 문을 위한 master값 설정
	FD_ZERO(&master);
	for (i=0; i<3; i++)
		FD_SET(fd[i], &master);

	// select 문의 timer 값 설정
	time = 30;
	t.tv_sec = time;
	while (set=master, select(fd[2]+1, &set, NULL, NULL, &t)>0){
		for (i=0; i<3; i++){
			if (FD_ISSET(fd[i], &set)){
				if (read(fd[i], buf, sizeof(buf)) > 0){
					printf("MSG from %d=%s\n", i, buf);
					n=strlen(buf);
					// 문자열의 길이 보내기
					write(fd[i+3], &n, sizeof(int));
				}
			}
		}
		// select 문의 timer 값 재설정
		t.tv_sec = time;
	}
	exit(0);
}
