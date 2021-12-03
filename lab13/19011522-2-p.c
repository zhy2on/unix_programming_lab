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

union semun{
	int val;
	struct semid_ds *buf;
	ushort *array;
};
int main(void){
	int fd, i, semid, val, len = 0, n;
	char *addr;
	key_t key;
	union semun arg;
	struct sembuf p_buf;

	key=ftok("key", 1);

	// semaphore 생성 및 초기화
	semid = semget(key, 1, 0600|IPC_CREAT|IPC_EXCL);
	if (semid == -1) {
		semid = semget(key, 1, 0);
	}
	else {
		arg.val = 10; //size of buf
		semctl(semid, 0, SETVAL, arg);
	}

	printf("semid: %d val: %d\n", semid, semctl(semid, 0, GETVAL, 0));

	// file open & memory mapping
	fd = open("data1", O_RDWR|O_CREAT, 0600);
	addr = mmap(NULL, 512, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	ftruncate(fd, 10);

	for (i=0; i<10; i++){
		// mapping된 공간으로 문자열 입력
		if (addr == 0)
			len = 0;
		n = read(0, addr + len, 512) - 1;
		(addr + len)[n] = '\0';
		len += n;
		printf("n: %d\n", n);
		if (strcmp("quit", addr + len) == 0)
			break ;

		printf("idx: %d buf: %s\n", i, addr + len - n);
		// semaphore wait
		p_buf.sem_num = 0;
		p_buf.sem_op = -n;
		p_buf.sem_flg = 0;
		semop(semid, &p_buf, 1);
	}
	exit(0);
}
