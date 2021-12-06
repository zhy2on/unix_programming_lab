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

void do_child(int semid, int *addr){
	int id, i, j;
	pid_t pid;
	struct sembuf p_buf;

	pid=getpid();
	// 한 번에 한 process 씩 출력 순서를 확인하기 위한 동기화 작업
	p_buf.sem_num = 0;
	p_buf.sem_op = -1;
	p_buf.sem_flg = 0;
	semop(semid, &p_buf, 1);

	// id 선택
	id = addr[++addr[0]];

	printf("pid=%d, id=%d\n", pid, id);

	// 한 번에 한 process 씩 출력 순서를 확인하기 위한 동기화 작업
	p_buf.sem_num = 0;	
	p_buf.sem_op = 1;
	p_buf.sem_flg = 0;
	semop(semid, &p_buf, 1);

	if (id == 1) {
		while (addr[0] != 5)
			sleep(1);
	}
	if (id>1){
		// 출력 순서가 될때까지 대기
		p_buf.sem_num = id - 1;
		p_buf.sem_op = -1;
		p_buf.sem_flg = 0;
		semop(semid, &p_buf, 1);
	}
	for (j=0; j<5; j++){
		printf("%ld\n", pid);
		sleep(1);
	}
	if (id<5){
		// 다음 출력 순서의 child process가 출력 가능하게 만들기
		p_buf.sem_num = id;
		p_buf.sem_op = 1;
		p_buf.sem_flg = 0;
		semop(semid, &p_buf, 1);
	}
	exit(0); // 이 부분의 코드는 변경하지 말 것
}

int main(void){
	ushort buf[5]={1, 0, 0, 0, 0};
	int i, fd, n, semid, *addr;
	key_t key;
	union semun arg;

	key=ftok("key", 5);

	// semaphore 생성 및 초기화
	semid = semget(key, 5, 0600|IPC_CREAT|IPC_EXCL);
	if (semid == -1)
		semid = semget(key, 5, 0);
	else {
		arg.array = buf;
		semctl(semid, 0, SETALL, arg);
	}
	printf("semid: %d\n", semid);

	fd=open("data", O_RDWR|O_CREAT, 0600);
	addr=mmap(NULL, sizeof(int)*6, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	// 파일 크기 조절
	ftruncate(fd, sizeof(int)*6);

	// mapping된 공간 초기화
	addr[0] = 0;
	for (i=1; i<6; i++){
		scanf("%d", (addr+i));
	}
	for (i=0; i<5; i++){ // 이 부분의 코드는 변경하지 말 것
		if (fork()==0){
			do_child(semid, addr);
		}
	}
	for(i=0; i<5; i++)
		wait(0);
	exit(0);
}
