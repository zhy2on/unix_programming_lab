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

int list(const char *name, const struct stat *status, int type) {
	int cnt;
	struct dirent *d;
	DIR *dp;
	if (type == FTW_D) {
		// 해당 directory가 비어있는지 확인하고 비어있는 경우에만
		cnt = 0;
		dp = opendir(name);
		while (d = readdir(dp)) {
			if (d->d_name[0] == '.')
				continue;
			cnt++;
		}
		// directory 이름 출력
		if (cnt == 0)
			printf("%s\n", name);
	}
	return 0;
}
int main(void) {
	// ftw 호출
	ftw(".", list, 1);
	return 0;
}
