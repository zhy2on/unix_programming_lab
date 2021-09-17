#include "/home/account/class/tspark/unix19011522/includes.h"

int main(void) {
	int fd, i;
	
	//(a)
	fd = open("data1", O_RDWR|O_CREAT|O_TRUNC, 0600);
	for (i = 0; i < 10; i++)
		write(fd, "X", 1);
	//(b)
	lseek(fd, 0, SEEK_SET);
	write(fd, "Y", 1);
	//(c)
	lseek(fd, 0, SEEK_END);
	write(fd, "Y", 1);
	//(d)
	for (i = 1; i < 9; i += 2) {
		lseek(fd, i, SEEK_SET);
		write(fd, "Z", 1);
	}
	//(e)
	lseek(fd, 14, SEEK_SET);
	write(fd, "T", 1);
	//(f)
	lseek(fd, -2, SEEK_END);
	write(fd, "S", 1);
	//(g)
	lseek(fd, -2, SEEK_CUR);
	write(fd, "W", 1);

	return (0);
}
