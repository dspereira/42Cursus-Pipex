#include "pipex.h"

#define STD_IN      0
#define STD_OUT     1

// gcc pipex.c set_std_io.c get_cmd.c ft_split.c

int main (int argc, char **argv)
{
    int infile_fd;
    int outfile_fd;
    char *path = "/usr/bin/cat";
    char *command[] = {"cat", 0}; 
    
    t_cmd *cmds;

    cmds = get_cmds(argc - 3, argv + 2);
    print_cmd(argc - 3, cmds);
    free_cmds(argc - 3, cmds);


   
   /* if (set_std_io("in.txt", "out.txt"))
    {
        write(STD_OUT, "Works!\n", 7);
    }
    if (execve(path, command, NULL) == -1)
    {
        write(STD_OUT, "Deu muito errado\n", 17);
    }
    */

    return (0);
}