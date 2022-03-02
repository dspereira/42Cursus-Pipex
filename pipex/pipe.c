#include "pipex.h"

int open_pipe(t_fd *p)
{
	int fd[2];
	int err;

	err = pipe(fd);
	if (!err)
	{
		p->r = fd[0];
		p->w = fd[1];
	}
	else
		perror(PROGRAM_NAME);
	return (err);
}

// talvez para retirar
int close_fd(int *fd)
{
	int err;
	err = close(*fd);
	if (!err)
		*fd = -1;
	else 
		printf("pipex: %s\n", strerror(errno));
	return (err);
}