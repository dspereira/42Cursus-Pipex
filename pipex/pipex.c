#include "pipex.h"

#define STD_IN      0
#define STD_OUT     1

// gcc pipex.c set_std_io.c get_cmd.c ft_split.c pipe.c get_path.c

int main (int argc, char **argv, char **envp)
{
    t_cmd *cmds;
    t_pipe p;
    int pid;
    char **paths;

    paths = get_path(envp);
    if (paths)
    {
        int i = 0;
        while (paths[i])
        {
            //printf("%s\n",paths[i]);
            i++;
        }
    }
    else 
        printf("Nao existe o path\n");

    cmds = get_cmds(argc - 3, (const char**)(argv + 2), (const char **)paths);

    //cmds = get_cmds(argc - 3, (const char**)(argv + 2));
    if (redirect_infile("in.txt") == -1)
        return (1);

    open_pipe(&p);

    pid = fork();
    if (pid == 0)
    {
        if (redirect_io(p.w_fd, STDOUT_FILENO) == -1)
            return (1);
        
        if (execve(cmds[0].path, cmds[0].cmd, NULL) == -1)
        {
            write(STD_OUT, "Deu muito errado\n", 17);
        }
        
    }
    else {
        close(p.w_fd);
        int status;
        waitpid(pid, &status, 0);
        if (status != 0)
            return (0);
        printf("waitpid status: %i\n", status);

        if (redirect_io(p.r_fd, STDIN_FILENO) == -1)
            return (1);
        
        printf("path: %s\n", cmds[1].path);
        printf("cmd: %s\n", cmds[1].cmd[0]);
        printf("flag: %s\n", cmds[1].cmd[1]);

        if (execve(cmds[1].path, cmds[1].cmd, NULL) == -1)
        {
            write(STD_OUT, "Deu muito errado\n", 17);
        }

        close(p.r_fd);
        free_cmds(argc - 3, cmds); 
    }
    

    return (0);
}