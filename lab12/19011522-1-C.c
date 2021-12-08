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

int main(int argc, char **argv) {	
	char f[6][3]={"f1", "f2", "f3", "f4", "f5", "f6"}; // 6개의 fifo 이름 정의
	char buf[512];
	int i, id, n, fd_r, fd_w;

	id=atoi(argv[1]);
	// id에 따라 적절한 fifo open
	fd_w = open(f[id], O_WRONLY);
	fd_r = open(f[id+3], O_RDONLY);

	for (i=0; i<3; i++){
		scanf("%s", buf);
		// server에게 문자열 보내기
		write(fd_w, buf, strlen(buf)+1);
		// server로부터 문자열의 길이 받기
		read(fd_r, &n, sizeof(int));
		printf("%d\n", n);
	}
	close(fd_w);
	exit(0);
}
