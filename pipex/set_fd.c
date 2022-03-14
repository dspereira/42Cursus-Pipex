#include "pipex.h"

t_fds *init_fds(void)
{
	t_fds *fds;

	fds = oom_guard(malloc(sizeof(t_fds)));
	fds->fd = 0;
	fds->size = 0;
	return (fds);
}

t_fd *init_fd(int num_fd)
{
	t_fd *fd;
	int i;

	fd = oom_guard(malloc(num_fd * sizeof(t_fd)));
	i = 0;
	while (i < num_fd)
	{
		fd[i].r = -1;
		fd[i].w = -1;
		i++;
	}
	return (fd);
}

t_fds *set_fd(char *infile, char *outfile, int size)
{
	t_fds *fds;
	t_fd *fd;
	int pipe_fd[2];
	int i;

	fds = init_fds();
	save_alloc_fds(fds);
	fds->fd = init_fd(size);
	fds->size = size;
	fd = fds->fd;
	fd[0].r = sys_error(open(infile, O_RDONLY));
	if (access(outfile, F_OK) == 0)
	{
		sys_error(access(outfile, W_OK));
		sys_error(unlink(outfile));
	}
	fd[size - 1].w = sys_error(open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 00644));
	i = 1;
	while (i < size - 1)
	{
		sys_error(pipe(pipe_fd));
		fd[i].r = pipe_fd[0];
		fd[i].w = pipe_fd[1];
		i++;
	}
	return (fds);
}

void close_fds(t_fds *fds)
{
	t_fd *fd;
	int i;

	if (!fds)
		return ;
	fd = fds->fd;
	i = 0;
	while (i < fds->size)
	{
		if (fd[i].r >= 0)
		{
			close(fd[i].r);
			fd[i].r = -1;
		}
		if (fd[i].w >= 0)
		{
			close(fd[i].w);
			fd[i].w = -1;
		}
		i++;
	}
	if (fd)
		free(fd);
	free(fds);
}