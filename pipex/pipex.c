#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define STD_IN      0
#define STD_OUT     1

int set_std_io(char *infile, char *outfile);

int main (int argc, char **argv)
{
    int infile_fd;
    int outfile_fd;
    char *path = "/usr/bin/cat";
    char *command[] = {"cat", 0}; 

    if (set_std_io("in.txt", "out.txt"))
    {
        write(STD_OUT, "Works!\n", 7);
    }
    if (execve(path, command, NULL) == -1)
    {
        write(STD_OUT, "Deu muito errado\n", 17);
    }
    return (0);
}