#include "../includes/pipex.h"

void	close_fds(t_fds *fds)
{
	t_fd	*fd;
	int		i;

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
	save_alloc_fds(0);
}
