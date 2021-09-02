#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int	fd, i;
	int	data = 35;
	
	if ((fd = open("./test2", O_WRONLY|O_CREAT, 0640)) < 0)
	{
		write(2, "open error\n", 11);
		return (1);
	}
	for (i = 0; i < 10; i++)
		write(fd, &data, sizeof(int));
	close(fd);
	return (0);
}
