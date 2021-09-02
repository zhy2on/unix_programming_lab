#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	int	data[10] = {0};
	int	fd, i;
	
	if ((fd = open("./test2", O_RDONLY)) < 0)
	{
		write(2, "open error\n", 11);
		return (1);
	}
	for (i = 0; i < 5; i++)
		read(fd, data + i, sizeof(int));
	for (i = 0; i < 10; i++)
		printf("%d ", data[i]);
	close(fd);
	return (0);
}
