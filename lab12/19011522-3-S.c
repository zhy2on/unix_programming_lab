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

struct q_entry {
	long mtype;
	int data;
};

int main(void) {
	int i, qid;
	key_t key;
	struct q_entry msg;

	key = ftok("key", 3);

	// message queue 만들고 open
	qid = msgget(key,IPC_CREAT|0600);

	for (i=0; i<15; i++) {
		// message 받기
		msgrcv(qid, &msg, sizeof(int), 0, 0);
		// mtype 조정
		msg.mtype = msg.mtype+3;
		msg.data += 8;
		// message 보내기
		msgsnd(qid, &msg, sizeof(int), 0);
	}
	return 0;
}
