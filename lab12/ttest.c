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
	char f[6][3] = { "f1", "f2", "f3", "f4", "f5", "f6" }; // 6개의 fifo 이름 정의
	char buf[512];
	int i, fd[6], n;
	fd_set set, master;
	struct timeval t;

	for (i = 0; i < 6; i++) {
		mkfifo(f[i], 0600);
		if(i%2==0){
			fd[i] = open(f[i], O_RDONLY);
		}
		else{
			fd[i] = open(f[i], O_WRONLY);
		}
	}

	FD_ZERO(&master);

	for(i = 0; i < 6; i+= 2){
		FD_SET(fd[i],&master);
	}

	t.tv_sec = 30;
	while (set = master, select(fd[5] + 1, &set, NULL, NULL, &t) > 0) {
		for (i = 0; i < 3; i++) {
			if (FD_ISSET(fd[2*i], &set)) {
				if (read(fd[2*i], buf, 512) > 0) {
					printf("MSG from %d=%s\n", i, buf);
					n = strlen(buf);
					write(fd[2*i + 1], &n, sizeof(int));
				}
			}
		}
		t.tv_sec = 30;
	}
	exit(0);
}
