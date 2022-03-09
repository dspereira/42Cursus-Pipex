#include "pipex.h"

int redirect_io(int oldfd, int newfd)
{
    int err;

    err = dup2(oldfd, newfd);
    if (err == -1)
    {
        perror("pipex234");
    }
    return(err);
}

int exec_cmd1(t_fds fds, t_cmd cmd, int i)
{
	int pid; 

	pid = fork();
	if (!pid)
	{
		if (redirect_io(fds.fd[i].r, STDIN_FILENO) == -1)
			return (-1);		
		if (redirect_io(fds.fd[i+1].w, STDOUT_FILENO) == -1)
			return (-1);
		close_fds(fds);

		if (execve(cmd.path, cmd.cmd, NULL) == -1)
		{
			write(STDOUT_FILENO, "Deu muito errado\n", 17);
		}
		exit(1);
	}
	return (0);
}


void exec_cmd(t_fds fds, t_cmd cmd, int i)
{
	int pid;

	pid = fork();
	if (!pid)
	{
		sys_error(dup2(fds.fd[i].r, STDIN_FILENO));
		sys_error(dup2(fds.fd[i+1].w, STDOUT_FILENO));
		close_fds(fds);
		sys_error(execve(cmd.path, cmd.cmd, NULL));
		exit(1);
	}
}