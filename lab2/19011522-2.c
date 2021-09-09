#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
	char n1[50], n2[50], buf[512];
	int fd1, fd2, n;

	scanf("%s %s", n1, n2);	
	if ((fd1 = open(n1, O_RDONLY)) < 0) {
		printf("%s : No such file...\n", n1);
		return (0);
	}
	if ((fd2 = open(n2, O_WRONLY|O_CREAT|O_EXCL, 0600)) < 0) {
		printf("%s : File already exists...Do you want to overwrite it?\n", n2);
		getchar();
		if (getchar() != 'Y')
			return (0);
		fd2 = open(n2, O_WRONLY|O_TRUNC);
	}
	while ((n = read(fd1, buf, 512)) > 0)
		write(fd2, buf, n);
	return (0);
}
