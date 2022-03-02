#include "pipex.h"

int open_pipe(t_pipe *p)
{
	int fd[2];
	int err;

	err = pipe(fd);
	p->r_fd = fd[0];
	p->w_fd = fd[1];
	if (err == -1)
		printf("pipex: %s\n", strerror(errno));
	return (err);
}

int close_pipe(t_pipe p)
{
	int err;

	err = close(p.r_fd);
	if (err == 0)
		err = close(p.w_fd);
	if (err == -1)
		printf("pipex: %s\n", strerror(errno));
	return (err);
}


int open_pipe1(t_fd *p)
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
		printf("pipex: %s\n", strerror(errno));
	return (err);
}

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