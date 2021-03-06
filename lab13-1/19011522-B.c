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

void set_sembuf(struct sembuf *p_buf, int snum, int sop) {
	p_buf->sem_num = snum;
	p_buf->sem_op = sop;
	p_buf->sem_flg = 0;
}

int main(void){
	ushort buf[2] = {1, 0};
	int i, j, pid, semid;
	key_t key;
	union semun arg;
	struct sembuf p_buf;

	key=ftok("key", 10);
	semid = semget(key, 2, 0600|IPC_CREAT|IPC_EXCL);// semaphore 생성
	if (semid==-1){
		// semaphore get
		semid = semget(key, 2, 0);
	}
	else{
		// semaphore 값 초기화
		arg.array = buf;
		semctl(semid, 0, SETALL, arg);
	}
	printf("semid: %d\n", semid);
	pid=getpid();
	for (i=0; i<3; i++){ 
		// 동기화를 위한 semaphore 연산
		set_sembuf(&p_buf, 1, -1);
		semop(semid, &p_buf, 1);
		for (j=0; j<3; j++){
			printf("%d ... %ld\n", i, pid);
			sleep(1);
		}
		// 동기화를 위한 semaphore 연산
		set_sembuf(&p_buf, 0, 1);
		semop(semid, &p_buf, 1);
	}
	return 0;
}
