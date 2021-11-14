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
	int fd, i;
	int *addr;
	fd=open("temp", O_RDWR);// 파일을 읽기, 쓰기 가능하게 open
		addr=mmap(NULL, sizeof(int) * 10,
			PROT_READ|PROT_WRITE, MAP_SHARED,
			fd, 0);// memory mapping
		ftruncate(fd, sizeof(int) * 10);
		for (i=0; i<10; i++){
			scanf("%d", addr+i);
		}
	exit(0);
}
