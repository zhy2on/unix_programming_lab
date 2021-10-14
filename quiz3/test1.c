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

int main(int argc, char **argv){
	int i, N1, N2;
	N1=atoi(argv[1]);
	N2=atoi(argv[2]);
	for (i=N1; i<=N2; i++){
		printf("%d\n", i);
		sleep(1);
	}
	return 0;
}
