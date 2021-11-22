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

void catchusr(int signo) {
}

int main(void) {
	int fd, i, len = 0, n;
	pid_t pid;
	char *addr;
	static struct sigaction act;

	act.sa_handler = catchusr;
	sigaction(SIGUSR1, &act, NULL);

	fd = open("data1", O_RDWR|O_CREAT, 0600);
	
	addr = mmap(NULL, 512, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	ftruncate(fd, 2048);

	pid = getpid();
	strncpy(addr, (char*)&pid, sizeof(pid_t));
	printf("B의 pid=%d\n", pid);
	
	pause();
	while (strcmp("quit", addr + len) != 0) {
		printf("reads ... %s\n", addr+len);
		len += strlen(addr+len);
		pause();
	}
	for (i = 0; i < len; i++)
		printf("%c", addr[i]);
	printf("\n");

	unlink("data1");
	printf("bye...\n");
	exit(0);
}
