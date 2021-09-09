#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
	char ch = 'K';
	int fd, i;

	if ((fd = open("./test1", O_WRONLY|O_CREAT|O_EXCL, 0640)) < 0) {
		printf("open error ............\n");
	}
	else {
		for (i = 0; i < 10; i++)
			write(fd, &ch, 1);	
	}
	return (0);
}
