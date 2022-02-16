#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main (int argc, char **argv)
{
    char *command[] = {"cat", "pipex.c", 0};
    char *bin_file = command[0];    

    int redirect_fd = open("file.txt", O_CREAT | O_TRUNC | O_WRONLY);
    dup2(redirect_fd, STDOUT_FILENO);
    close(redirect_fd);

    if (execvp(bin_file, command) == -1)
    {
        printf("DEU MUITO ERRADO");
    }
    return (0);
}