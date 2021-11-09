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
	int fd, n;
	pid_t pid;

	if ((fd = open("./data1", O_RDWR | O_CREAT, 0644)) < 0)
		return (-1);
	
	while ((n = read(fd, &pid, sizeof(pid_t))) != sizeof(pid_t))
		sleep(1);

	while (1) {
		scanf("%d", &n);
		if (n < 0)
			break;
		printf("writes .... %d\n", n);
		write(fd, &n, sizeof(int));
		sleep(1);
		kill(pid, SIGUSR1);
	}
	kill(pid, SIGUSR1);
	printf("bye...\n");
	return (0);
}
