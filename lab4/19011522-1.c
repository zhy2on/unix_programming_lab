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

int main(void) {
	if (!access("data1", F_OK))
	{
		printf("File exist.\n");
		if (!access("data1", R_OK|W_OK))
			printf("Read Write OK.\n");
	}
	else
		printf("File doesn't exist.\n");
	
	return 0;
}
