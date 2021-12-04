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
	int fd, i, semid;
	char *addr, c;
	key_t key;
	union semun arg;
	struct sembuf p_buf;
	ushort buf[2] = {0, 10};

	key=ftok("key", 1);

	// semaphore 생성 및 초기화
	semid = semget(key, 2, 0600|IPC_CREAT|IPC_EXCL);
	if (semid == -1) {
		semid = semget(key, 2, 0);
	}
	else {
		arg.array = buf; //fill cnt, empty cnt
		semctl(semid, 0, SETALL, arg);
	}

	printf("semid: %d\n", semid);

	// file open & memory mapping
	fd = open("data1", O_RDWR|O_CREAT, 0600);
	addr = mmap(NULL, 512, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

	i = 0;
	while (1){
		scanf("%c", &c);
		if (c != 'R')
			continue;
		//semWait(f)
		p_buf.sem_num = 0;
		p_buf.sem_op = -1;
		p_buf.sem_flg = 0;
		semop(semid, &p_buf, 1);

		//consume
		printf("idx: %d buf: %s\n", (i%10), addr+(512*(i%10)));
		memset(addr+(512*(i%10)), 0, 512);
		i++;

		//semSignal(e)
		p_buf.sem_num = 1;
		p_buf.sem_op = 1;
		p_buf.sem_flg = 0;
		semop(semid, &p_buf, 1);
	}
	exit(0);
}
