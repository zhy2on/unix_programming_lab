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

int main(void){
	// 프로세스 id, 프로세스 그룹 id, session id 출력
	printf("%ld %ld %ld\n", getpid(), getpgid(0), getsid(0));
	return 0;
}
