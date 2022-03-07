#include "pipex.h"

// gcc pipex.c get_cmd.c pipe.c get_path.c exec_cmd.c set_fd.c 

int main (int argc, char **argv, char **envp)
{
    int size;
    t_fds fds;
    t_cmd *cmds;
    char **paths;
    
    size = argc - 2;
    paths = get_path(envp);
    cmds = get_cmds(argc - 3, (const char**)(argv + 2), (const char **)paths);
    fds = set_fd(argv[1], argv[argc - 1], size);
    
    close_fds(fds);
    free_cmds(argc - 3, cmds);
}

