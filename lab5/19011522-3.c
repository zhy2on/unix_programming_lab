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

int main(int argc, char **argv){
	int i;
	// 함수의 인자로 주어진 문자열의 개수 출력
	printf("%d\n", argc - 1);
	i=0;
	while(argv[++i]){
		// 함수의 인자로 주어진 문자열 출력
		printf("%s\n", argv[i]);
	}
	return 0;
}

