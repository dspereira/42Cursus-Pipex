#include "pipex.h"

int redirect_io(int oldfd, int newfd)
{
    int err;

    err = dup2(oldfd, newfd);
    if (err == -1)
    {
        perror("pipex");
    }
    return(err);
}

int exec_cmd(t_fds fds, t_cmd cmd, int i)
{
	int pid; 

	pid = fork();

	if (!pid)
	{
		printf("read: %i\n", fds.fd[i].r);
		printf("write: %i\n", fds.fd[i+1].w);
		if (redirect_io(fds.fd[i].r, STDIN_FILENO) == -1)
			return (-1);		
		if (redirect_io(fds.fd[i+1].w, STDOUT_FILENO) == -1)
			return (-1);
		close_fds(fds);			
		if (execve(cmd.path, cmd.cmd, NULL) == -1)
		{
			write(STDOUT_FILENO, "Deu muito errado\n", 17);
		}
	}
	return (0);
}
