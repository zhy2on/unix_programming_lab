#include "/home/account/class/tspark/unix19011522/includes.h"

void cat_m(char **res){     	
	char buf[512];
	int fd, n;

	if ((fd = open(res[1], O_RDONLY)) < 0)
		return ;
	while ((n = read(fd, buf, sizeof(buf))) > 0)
		write(1, buf, n);
}

void cp_m(char **res){     	
	char buf[512];
	int fd1, fd2, n;

	if ((fd1 = open(res[1], O_RDONLY)) < 0)
		return ;
	fd2 = open(res[2], O_WRONLY|O_CREAT|O_TRUNC, 0600);
	while ((n = read(fd1, buf, sizeof(buf))) > 0)
		write(fd2, buf, n);
}

void vi_m(char **res){     	
	char buf[512];
	int fd, n;

	if ((fd = open(res[1], O_WRONLY|O_CREAT|O_EXCL, 0600)) < 0) {
		fd = open(res[1], O_RDWR);
		while ((n = read(fd, buf, sizeof(buf)))> 0)
			write(1, buf, n);
	}
	while (1) {
		n = read(0, buf, sizeof(buf));
		if (strcmp(buf, "quit") == 0)
			return ;
		write(fd, buf, n);
		for (int i = 0; i < n; i++)
			buf[i] = 0;
	}
}

int main(void){              	
	char in[50], *res[20]={0};
	char *inst[3]={"cat", "cp", "vi"};
	void (*f[3])(char **)={cat_m, cp_m, vi_m};
	int i;

	while (1){
		printf("> ");
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

		for (i=0;i<3;i++){
			if (!strcmp(res[0], inst[i])){
				f[i](res);
				break;
			}
		}
	}
}
