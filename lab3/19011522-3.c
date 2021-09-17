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
	struct stat buf;

	// buf에 “data3 파일의 속성을 저장
	stat("data3", &buf);
	
	// mode, link수, 크기 출력
	printf("%o, %ld, %ld\n", buf.st_mode&0777, buf.st_nlink, buf.st_size);
	
	return 0;

}
