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
	int fd, i, len=0, n;
	pid_t pid;
	char *addr, buf[512];
	static struct sigaction act;

	act.sa_handler = catchsig;
	sigaction(SIGUSR1, &act, NULL);

	fd = open("temp", O_RDWR|O_CREAT|O_TRUNC, 0600);

	pid = getpid();
	write(fd, &pid, sizeof(pid_t));

	addr = mmap(NULL, 50, PROT_READ | PROT_WRITE,
			MAP_SHARED, fd, 0);
	//printf("wait ...\n");
	pause();
	//printf("start!\n");
	for (i = 0; i < 3; i++) {
		n = read(0, buf, sizeof(buf));
		buf[n] = '\0';
		ftruncate(fd, len + n + 1);
		strcpy(addr + len, buf);
		len += n;
		pause();
	}
	exit(0);
}

void catchsig(int signo) {
}
