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

void catchalarm(int);
int main(void){
	int i, num, sum=0;
	sigset_t mask;
	static struct sigaction act;

	// SIGALRM signal 처리가 가능하도록 설정
	act.sa_handler = catchalarm;
	sigaction(SIGALRM, &act, NULL);

	for (i=0; i<10; i++){
		// 10초간 입력이 없으면, SIGALRM이 오도록 설정
		alarm(10);
		// 입력받기
		scanf("%d", &num);
		// 입력을 받으면, 알람 꺼두기
		if (alarm(0) == 0) {
			i--;
			continue;
		}
		sum+=num;
		printf("sum=%d\n", sum);

	}
	exit(0);
}
void catchalarm(int signo){
	printf("input !!! input !!! input !!!\n");
}
