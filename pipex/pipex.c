#include "pipex.h"

#define STD_IN      0
#define STD_OUT     1

// gcc pipex.c set_std_io.c get_cmd.c ft_split.c

int main (int argc, char **argv)
{
    t_cmd *cmds;

    cmds = get_cmds(argc - 3, (const char**)(argv + 2));
    print_cmd(argc - 3, cmds);

    if (set_std_io("in.txt", "out.txt"))
    {
        write(STD_OUT, "Works!\n", 7);
    }
    if (execve(cmds[0].path, cmds[0].cmd, NULL) == -1)
    {
        write(STD_OUT, "Deu muito errado\n", 17);
    }
    
    free_cmds(argc - 3, cmds);
    return (0);
}