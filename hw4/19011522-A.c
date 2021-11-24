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
	// 필요한 변수선언
	int fd, n, len = 0;
	pid_t pid;
	char *addr;

	fd=open("data1", O_RDWR);// “data1” 파일 open
	if (fd==-1){
		printf("Reader Not Ready....\n");
		return 0;
	}

	addr = mmap(NULL, 512, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0); // memory mapping
	while((n = read(fd, &pid, sizeof(pid_t))) == 0){
		sleep(3);
	}

	printf("B의 pid=%d\n", pid);

	n = read(0, addr, 512) - 1;
	addr[n] = '\0';
	while (strcmp("quit", addr + len) != 0) {
		printf("writes ..... %s\n", addr + len);
		kill(pid, SIGUSR1);
		len += n;
		n = read(0, addr + len, 512) - 1;
		(addr + len)[n] = '\0';
	}
	// B에게 signal 보내기
	kill(pid, SIGUSR1);
	printf("bye...\n");
	exit(0);
}
