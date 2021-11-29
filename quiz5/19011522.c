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


void do_child(int p[5][2]){
	char buf='a';
	int i, pid=getpid(), id, in;

	// 자신의 출력 순서 전달받음
	read(p[0][0], &id, sizeof(int));
	printf("pid=%d, id=%d\n", pid, id);

	// 자신의 출력 순서까지 대기
	if (id != 1)
		read(p[id-1][0], &in, sizeof(int));

	for(i=0; i<5; i++){
		sleep(1);
		printf("%ld\n", pid);
	}
	// 다음 순서의 child에게 공지
	if (id < 5)
		write(p[id][1], &id, sizeof(int));;

	exit(0); // 이 부분의 코드는 수정하면 안 됩니다.
}

int main(void) {	
	int i, in, pid, p[5][2];

	for(i=0; i<5; i++)
		pipe(p[i]);
	for (i=0; i<5; i++){
		scanf("%d", &in);
		// child들에게 출력 순서 공지를 위한 작업
		write(p[0][1], &in, sizeof(int));
	}

	for (i=0; i<5; i++){ // 이 부분의 코드는 수정하면 안 됩니다.
		if (fork()==0){
			do_child(p);
		}
	}
	for(i=0; i<5; i++)
		wait(0);
	exit(0);
}
