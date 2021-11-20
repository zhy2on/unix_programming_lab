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

void do_second_child(int p1[2], int p2[2]) {
	int in;

	read(p1[0], &in, sizeof(int));
	printf("2nd level : %d\n", in);
	write(p2[1], &in, sizeof(int));

	exit(0);
}

void do_first_child(int p1[2], int p2[2]) {
	int pip1[2], pip2[2], in;

	pipe(pip1);
	pipe(pip2);
	if (fork() == 0)
		do_second_child(pip1, pip2);
	
	read(p1[0], &in, sizeof(int));
	write(pip1[1], &in, sizeof(int));

	read(pip2[0], &in, sizeof(int));
	printf("1st level : %d\n", in);
	write(p2[1], &in, sizeof(int));

	wait(0);
	exit(0);
}

void parent(int p1[2][2], int p2[2][2]) {
	int n1, n2;

	scanf("%d %d", &n1, &n2);

	write(p1[0][1], &n1, sizeof(int));
	write(p1[1][1], &n2, sizeof(int));

	read(p2[0][0], &n1, sizeof(int));
	read(p2[1][0], &n2, sizeof(int));

	printf("parent: %d %d\n", n1, n2); 
}

int main(void) {
	int pip1[2][2], pip2[2][2], in, i;

	for (i = 0; i < 2; i++) {
		pipe(pip1[i]);
		pipe(pip2[i]);
		if (fork() == 0)
			do_first_child(pip1[i], pip2[i]);
	}

	parent(pip1, pip2);

	for (i = 0; i < 2; i++) {
		wait(0);
	}
	exit(0);
}

