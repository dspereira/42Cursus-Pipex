#include "pipex.h"

t_fds *set_fd(char *infile, char *outfile, int size)
{
    t_fds *fds;
    t_fd *fd;
    int pipe_fd[2];
    int i;

    fds = malloc(sizeof(t_fds));
    fds->fd = malloc(size * sizeof(t_fd));
    fds->size = size;
    i = 0;
    while (i < size)
    {
        fds->fd[i].r = -1;
        fds->fd[i].w = -1;
        i++;
    }
    fd = fds->fd;
    save_alloc_fds(fds);
    fd[0].r = sys_error(open(infile, O_RDONLY));
    fd[0].w = -1;
    fd[size - 1].w = sys_error(open(outfile, O_TRUNC | O_WRONLY));
    fd[size - 1].r = -1;
    i = 1;
    while (i < size - 1)
    {
        sys_error(pipe(pipe_fd));
        fd[i].r = pipe_fd[0];
		fd[i].w = pipe_fd[1];
        i++;
    }
    //fds->size = size;
    save_alloc_fds(fds);
    return (fds);
}

void close_fds(t_fds *fds)
{
    t_fd *fd = 0;
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