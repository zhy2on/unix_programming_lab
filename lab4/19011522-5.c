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
	struct stat buf;
	char sym[100] = {0};
	char real[100] = {0};

	scanf("%s", sym);
	lstat(sym, &buf);
	printf("symname: %s permision: %o, size: %ld\n", sym, buf.st_mode&0777, buf.st_size);

	stat(sym, &buf);	
	readlink(sym, real, 99);
	printf("realname: %s permision: %o, size: %ld\n", real,  buf.st_mode&0777, buf.st_size);

	return 0;
}
