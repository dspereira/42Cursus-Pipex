#include "pipex.h"

int exec_cmd(int in_fd, int out_fd, t_cmd cmd)
{
	int pid;

	pid = fork();

	if (!pid)
	{
		if (redirect_io(in_fd, STDIN_FILENO) == -1)
			return (-1);		
		if (redirect_io(out_fd, STDOUT_FILENO) == -1)
			return (-1);		
		if (execve(cmd.path, cmd.cmd, NULL) == -1)
		{
			write(STDOUT_FILENO, "Deu muito errado\n", 17);
		}
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(in_fd);
		close(out_fd);
	}
	return (0);
}
