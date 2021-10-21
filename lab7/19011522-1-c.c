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

int main(int ac, char **av) {
	int fd, i;
	char buf;

	fd = open("./data", O_RDONLY);
	if (fd > 0) {
		for (i = 0; i < 10; i++) {
			if (read(fd, &buf, 1) > 0)
				printf("%c\n", buf);
			sleep(1);
		}
	}
	exit(3);
}
