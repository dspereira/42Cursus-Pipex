#include "pipex.h"

t_fds set_fd(char *infile, char *outfile, int size)
{
    t_fds fds;
    t_fd *fd;
    int pipe_fd[2];
    int i;

    fd = malloc(size * sizeof(t_fd));
    fd[0].r = sys_error(open(infile, O_RDONLY));
    fd[0].w = -1;
    fd[size - 1].w = sys_error(open(outfile, O_TRUNC | O_WRONLY));
    fd[size - 1].r = -1;
    i = 1;
    int pipe_fd1[1];
    while (i < size - 1)
    {
        sys_error(pipe(pipe_fd));
        fd[i].r = pipe_fd[0];
		fd[i].w = pipe_fd[1];
        i++;
    }
    fds.size = size;
    fds.fd = fd;
    return (fds);
}

int close_fds(t_fds fds)
{
    t_fd *fd;
    int i;

    fd = fds.fd;
    i = 0;
    while (i < fds.size)
    {
        if (fd[i].r >= 0)
            sys_error(close(fd[i].r));
        if (fd[i].w >= 0)
            sys_error(close(fd[i].w));
        i++;
    }
    free(fd);
    return (0);
}