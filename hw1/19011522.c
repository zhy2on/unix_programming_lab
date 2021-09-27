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

void cat_m(char **res){
	char buf[512];
	int fd, n;

	if ((fd = open(res[1], O_RDONLY)) > 0) {
		while ((n = read(fd, buf, sizeof(buf))) > 0)
			write(1, buf, n);
	}
}
void cd_m(char **res){
	chdir(res[1]);
}
void cp_m(char **res){
	char buf[512];
	int fd1, fd2, n;

	if ((fd1 = open(res[1], O_RDONLY)) > 0) {
		fd2 = open(res[2], O_WRONLY|O_CREAT|O_TRUNC, 0600);
		while ((n = read(fd1, buf, sizeof(buf))) > 0)
			write(fd2, buf, n);
	}
}
void mkdir_m(char **res){
	mkdir(res[1], 0700);
}
void ls_m(char **res){
	DIR *dp;
	struct dirent *d;
	struct stat buf;

	dp = opendir(".");
	while (d = readdir(dp)) {
		if (d->d_name[0] == '.')
			continue;
		stat(d->d_name, &buf);
		printf("%c %04o %ld %ld %ld %ld %s %s\n", S_ISDIR(buf.st_mode) ? 'D' : 'F', buf.st_mode&0777, buf.st_nlink, buf.st_uid, buf.st_gid, buf.st_size, strtok(ctime(&buf.st_mtime), "\n"), d->d_name);
	}
}
int main(void){
	char path[100] = {0};
	char in[50], *res[20]={0};
	char *inst[5]={"cat", "cd", "cp", "mkdir", "ls"};
	void (*f[5])(char **)={cat_m, cd_m, cp_m, mkdir_m, ls_m};
	int i;

	while (1){
		printf("%s> ", getcwd(path, 99));
		
		gets(in);
		if (in[0]=='\0')
			continue;
		i=0;
		res[i]=strtok(in, " ");
		while (res[i]){
			i++;
			res[i]=strtok(NULL, " ");
		}
		if (strcmp(res[0], "exit")==0)
			exit(0);
		for (i=0;i<5;i++){
			if (!strcmp(res[0], inst[i])){
				f[i](res);
				break;
			}
		}
	}
}
