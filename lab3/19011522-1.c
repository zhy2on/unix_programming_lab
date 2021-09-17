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
	int i, fd, data1[10], data2[10];

	for (i=0;i<10;i++){
		scanf("%d", &data1[i]);
	}
	
	//배열 data1[]에 저장 된 정수를 "data1" 파일에 저장한다.
	fd = open("data1", O_RDWR|O_CREAT, 0600);
	for (i=0;i<10;i++)
		write(fd, data1 + i, sizeof(int));
	lseek(fd, 0, SEEK_SET);

	//"data1" 파일에 저장된 정수를 읽어 data2[] 배열에 저장한다.
	for (i=0;i<10;i++)
		read(fd, data2 + i, sizeof(int));

	for (i=0;i<10;i++){
		printf("%-5d", data1[i]);
	}
	printf("\n");
	for (i=0;i<10;i++){
		printf("%-5d", data2[i]);
	}
	printf("\n");

	return 0;
}
