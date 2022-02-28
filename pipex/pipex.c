#include "pipex.h"

#define STD_IN      0
#define STD_OUT     1

// gcc pipex.c set_std_io.c get_cmd.c ft_split.c pipe.c get_path.c exec_cmd.c

int main (int argc, char **argv, char **envp)
{
    t_cmd *cmds;
    t_pipe p;
    int pid;
    char **paths;
    int infile_fd;
    int outfile_fd;

    paths = get_path(envp);
    if (!paths)
        printf("Nao existe o path\n");

    cmds = get_cmds(argc - 3, (const char**)(argv + 2), (const char **)paths);    
    infile_fd = open("in.txt", O_RDONLY);
    if (infile_fd < 0)
        return (0);
    outfile_fd = open("out.txt", O_TRUNC | O_WRONLY);
    if (outfile_fd < 0)
        return (0);

    open_pipe(&p);
    exec_cmd(infile_fd, p.w_fd, cmds[0]);
    close(p.w_fd);
    exec_cmd(p.r_fd, outfile_fd, cmds[1]);
    close(p.r_fd);

    free_cmds(argc - 3, cmds);
    
    return (0);
}