
#include "pipex.h"

int set_std_io(char *infile, char *outfile)
{
    int in_fd;
    int out_fd;

    if (access(infile, R_OK) == -1)
    {
        printf("pipex: %s\n", strerror(errno));
        return(0);
    }
    if (access(outfile, W_OK) == -1){
        printf("pipex: %s\n", strerror(errno));
        return(0);
    }

    in_fd = open(infile, O_RDONLY);
    if (in_fd)
    {
        dup2(in_fd, STDIN_FILENO);
        close(in_fd);
    }
    else 
    {
        printf("pipex: %s\n", strerror(errno));
        return(0);  
    }
    out_fd = open(outfile, O_TRUNC | O_WRONLY);
    if (out_fd)
    {
        dup2(out_fd, STDOUT_FILENO);
        close(out_fd);
    }
    else 
    {
        printf("pipex: %s\n", strerror(errno));
        return(0);  
    }
    return (1);
}

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

}