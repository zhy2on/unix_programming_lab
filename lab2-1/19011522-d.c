#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	char	ch = 'Z';
	int	fd, i;

	if ((fd = open("./test1", O_WRONLY|O_APPEND)) < 0)
	{
		write(2, "open error\n", 11);
		return (1);
	}
	for (i = 0; i < 5; i++)
		write(fd, &ch, 1);
	close(fd);
	return (0);
}
