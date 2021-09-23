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
	char ch1[100] = {0};
	char ch2[100] = {0};

	scanf("%s %s", ch1, ch2);
	if (access(ch1, F_OK))
	{
		printf("File does not exist\n");
		return 0;
	}
	if (!link(ch1, ch2))
		printf("Success\n");
	else
		printf("Fail\n");

	return 0;
}
