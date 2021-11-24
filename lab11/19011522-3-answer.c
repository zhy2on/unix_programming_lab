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

void do_child2(int id, int p[2][2]) {
	int N, pid=getpid();

	read(p[0][0], &N, sizeof(int));
	printf("2nd level %d reads %d from parent ... \n", pid, N);

	N++;
	write(p[1][1], &N, sizeof(int));

	exit(0);
}

void do_child1(int id, int p[4][2]) {
	int i, N, M, pid=getpid(), q[2][2];

	read(p[id][0], &N, sizeof(int));
	printf("1st level %d reads %d from parent ... \n", pid, N);
	for (i=0; i<2; i++)
		pipe(q[i]);
	if(fork()==0) {
		do_child2(i, q);
	}

	write(q[0][1], &N, sizeof(int));
	read(q[1][0], &N, sizeof(int));
	printf("1st level %d reads %d from 2nd level child ... \n", pid, N);
	write(p[id+2][1], &N, sizeof(int));

	wait(0);
	exit(0);
}

int main(void) {	
	int i, N, M, p[4][2];

	for(i=0; i<4; i++)
		pipe(p[i]);

	for(i=0; i<2; i++) {
		if (fork() == 0) {
			do_child1(i, p);
		}
	}

	scanf("%d %d", &N, &M);
	write(p[0][1], &N, sizeof(int));
	write(p[1][1], &M, sizeof(int));

	read(p[2][0], &N, sizeof(int));
	read(p[3][0], &M, sizeof(int));

	printf("parent reads .... %d and %d\n", N, M);
	for(i=0; i<2; i++)
		wait(0);
	exit(0);
}

