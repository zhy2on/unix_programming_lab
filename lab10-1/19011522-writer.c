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
	fd= open("temp", O_RDONLY);// 파일을 읽기 가능하게 open
		addr=mmap(NULL, 10 * sizeof(int),
			PROT_READ, MAP_SHARED,
			fd, 0);// memory mapping
		sleep(5);
	for (i=0; i<5; i++){
		printf("%d\n", *(addr+i));
	}
	sleep(5);
	for (i=5; i<10; i++){
		printf("%d\n", *(addr+i));
	}
	exit(0);
}
