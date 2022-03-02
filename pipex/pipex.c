#include "pipex.h"

#define STD_IN      0
#define STD_OUT     1

// gcc pipex.c set_std_io.c get_cmd.c ft_split.c pipe.c get_path.c exec_cmd.c



void set_cmd_fd(t_fd *cmd_fd, int *r_fd, int *w_fd)
{
    cmd_fd->r = *r_fd;
    cmd_fd->w = *w_fd;
    *r_fd = -1;
    *w_fd = -1;
}

int get_cmd_fd(t_fd *cmd_fd, t_fd *pipe_fd, char *infile, char *outfile)
{
    int r_fd;
    int w_fd;

    if (infile)
    {
        r_fd = open("in.txt", O_RDONLY);
        if (r_fd < 0)
            return (r_fd);
        set_cmd_fd(cmd_fd, &r_fd, &(pipe_fd[0].w));  
    }
    else if (outfile)
    {
       w_fd = open("out.txt", O_TRUNC | O_WRONLY);
        if (w_fd < 0)
            return (w_fd);
        if (pipe_fd[0].w == -1)
            r_fd = pipe_fd[0].r; 
        else 
            r_fd = pipe_fd[1].r;    
        set_cmd_fd(cmd_fd, &r_fd, &w_fd);
    }
    else if (pipe_fd[0].w == -1 && pipe_fd[0].r > 0)
        set_cmd_fd(cmd_fd, &(pipe_fd[0].r), &(pipe_fd[1].w));  
    else 
        set_cmd_fd(cmd_fd, &(pipe_fd[1].r), &(pipe_fd[0].w));
    return (0);
}

int main (int argc, char **argv, char **envp)
{
    t_cmd *cmds;
    t_fd pipe_fd[2];
    t_fd cmd_fd;
    char **paths;
    int size;

    size = argc - 3;
    paths = get_path(envp);
    if (!paths)
        printf("Nao existe o path\n");
    cmds = get_cmds(argc - 3, (const char**)(argv + 2), (const char **)paths);    
    int i = 0;
    while (i < size)
    {
        open_pipe1(&pipe_fd[i%2]);
        if (i == 0)
            get_cmd_fd(&cmd_fd, pipe_fd, "teste", 0);
        else if (i == size -1)
            get_cmd_fd(&cmd_fd, pipe_fd, 0, "teste");
        else
            get_cmd_fd(&cmd_fd, pipe_fd, 0, 0);
        exec_cmd(cmd_fd.r, cmd_fd.w, cmds[i]);
        i++;
    }
    free_cmds(argc - 3, cmds);
    return (0);
}