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

struct buffer{
	int f, r;
	char msg[10][512];
};

int main(void){
	char tmp[512];
	ushort buf[2] = {10,0};
	int fd, i, semid, n;
	key_t key;
	union semun arg;
	struct buffer *msg_buf;
	struct sembuf p_buf;

	key=ftok("key", 1);

	// semaphore 생성 및 초기화
	semid = semget(key, 2, 0600|IPC_CREAT|IPC_EXCL);
	if (semid == -1) {
		semid = semget(key, 2, 0);
	}
	else {
		arg.array = buf;
		semctl(semid, 0, SETALL, arg);
	}

	printf("semid: %d\n", semid);

	// file open & memory mapping
	fd = open("data1", O_RDWR|O_CREAT, 0600);
	msg_buf = mmap(NULL, sizeof(struct buffer), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

	while (1){
		scanf("%s", tmp);
		if (*tmp != 'R')
			continue;

		//semWait(e)
		p_buf.sem_num = 1;
		p_buf.sem_op = -1;
		p_buf.sem_flg = 0;
		semop(semid, &p_buf, 1);

		//append
		printf("idx: %d msg: %s\n", msg_buf->f, msg_buf->msg[msg_buf->f]);
		(msg_buf->f)++;
		(msg_buf->f)%=10;

		//semSignal(f)
		p_buf.sem_num = 0;
		p_buf.sem_op = 1;
		p_buf.sem_flg = 0;
		semop(semid, &p_buf, 1);
	}

	semctl(semid, 0, IPC_RMID, 0);
	exit(0);
}
