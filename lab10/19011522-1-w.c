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

int main(void){
	int fd, i, n, len=0;
	pid_t pid;
	char *addr;

	fd = open("temp", O_RDONLY);// 파일을 읽기 가능하게 open
	while ((n = read(fd, &pid, sizeof(pid_t))) != sizeof(pid_t))
		sleep(1);

	//printf("connect pid: %d\n", pid);
	kill(pid, SIGUSR1);

	addr= mmap(NULL, 50, PROT_READ,
			MAP_PRIVATE, fd, 0);// memory mapping

	for (i=0; i<3; i++){
		sleep(5);
		// 읽은 내용을 write로 화면 출력
		write(1, "-------\n", 8);
		write(1, addr + len, strlen(addr + len));
		len = strlen(addr);
		kill(pid, SIGUSR1);
	}
	exit(0);
}
