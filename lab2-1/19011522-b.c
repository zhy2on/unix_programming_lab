#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int	data;
	int	fd;
	int	i;
	
	data = 35;
	fd = open("./test2", O_WRONLY|O_CREAT, 0640);
	if (fd < 0)
		write(2, "open error\n", 11);
	for (i = 0; i < 10; i++)
		write(fd, &data, sizeof(int));
	close(fd);
	return (0);
}
