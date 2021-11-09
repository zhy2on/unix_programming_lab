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

int main(void) {	
	int fd, n;
	struct sigaction act;
	pid_t pid;
	
	act.sa_handler = catchsig;
	sigaction(SIGUSR1, &act, NULL);

	if ((fd = open("./data1", O_RDWR)) < 0)
		return (-1);		

	pid = getpid();
	write(fd, &pid, sizeof(pid_t));

	while (1) {
		pause();
		if (read(fd, &n, sizeof(int)) != sizeof(int))
			break;
		printf("reads... %d\n", n);
	}
	printf("bye...\n");
	return (0);
}

void catchsig(int signo) {
}
