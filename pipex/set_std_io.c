#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

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
    out_fd = open(outfile, O_WRONLY);
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