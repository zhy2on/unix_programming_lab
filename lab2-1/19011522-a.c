#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	char	ch;
	int	fd;
	int	i;

	ch = 'X';
	fd = open("./test1", O_WRONLY|O_CREAT, 0600);
	if (fd < 0)
		write(2, "open error\n", 11);
	for (i = 0; i < 10; i++)
		write(fd, &ch, 1);
	close(fd);
	return (0);
}
