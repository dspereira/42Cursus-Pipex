#include "../includes/pipex.h"

t_fds	*init_fds(void)
{
	t_fds	*fds;

	fds = oom_guard(malloc(sizeof(t_fds)));
	fds->fd = 0;
	fds->size = 0;
	return (fds);
}

t_fd	*init_fd(int num_fd)
{
	t_fd	*fd;
	int		i;

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

void	create_pipes(t_fd *fd, int size)
{
	int	i;
	int	fd_p[2];

	i = 0;
	while (i < size)
	{
		sys_error(pipe(fd_p));
		fd[i].r = fd_p[0];
		fd[i].w = fd_p[1];
		i++;
	}
}

/*
	Return: return a pointer of type t_fds
			the t_fds pointer have un array of t_fd.
			t_fd *fd:
				fd[0]					-> for infile fd
				fd[btw first and last]	-> for pipes fd
				fd[last pos]			-> for outfile
*/
t_fds	*get_fds(char *infile, char *outfile, int size)
{
	t_fds	*fds;
	t_fd	*fd;

	fds = init_fds();
	save_alloc_fds(fds);
	fds->fd = init_fd(size);
	fds->size = size;
	fd = fds->fd;
	if (access(outfile, F_OK) == 0)
	{
		sys_error(access(outfile, W_OK));
		sys_error(unlink(outfile));
	}
	fd[size - 1].w = sys_error(open(outfile, O_CREAT | O_WRONLY, 00644));
	fd[0].r = file_not_found_err(open(infile, O_RDONLY), infile);
	create_pipes(&fd[1], size - 2);
	return (fds);
}