
#include "pipex.h"

int redirect_io(int oldfd, int newfd)
{
    int err;

    err = dup2(oldfd, newfd);
    if (err == -1)
        printf("pipex: %s\n", strerror(errno));
    return(err);
}

int redirect_infile(const char *infile)
{
    int fd;
    int err;

    err = 0;
    fd = open(infile, O_RDONLY);
    if (fd >= 0)
    {
        err = dup2(fd, STDIN_FILENO);
        err = close(fd);
    }
    else
        err = -1;
    if (err == -1)
        printf("pipex: %s\n", strerror(errno));
    return(err);
}

int redirect_outfile(int oldfd, const char *outfile)
{
    return (0);
}