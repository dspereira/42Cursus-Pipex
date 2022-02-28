#include "pipex.h"

int exec_cmd(int in_fd, int out_fd, t_cmd cmd)
{
	int pid;

	pid = fork();

	if (!pid)
	{
		if (redirect_io(in_fd, STDIN_FILENO) == -1)
			return (-1);		
		if (out_fd != 10)
		{
			if (redirect_io(out_fd, STDOUT_FILENO) == -1)
				return (-1);
		}
		if (execve(cmd.path, cmd.cmd, NULL) == -1)
		{
			//write(STD_OUT, "Deu muito errado\n", 17);
		}
	}
	else
		waitpid(pid, NULL, 0);
	return (0);
}

/*
int exec_cmd1(char *infile, int out_fd, t_cmd cmd)
{
	int pid;

	pid = fork();
	if (pid == 0)
		if (redirect_infile(infile) == -1)
			return (1);
		if (redirect_io(out_fd, STDOUT_FILENO) == -1)
			return (1);
		if (execve(cmd.path, cmd.cmd, NULL) == -1)
		{
			//write(STD_OUT, "Deu muito errado\n", 17);
		}
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
	return (0);
}

int exec_cmd2(int in_fd, char *outfile, t_cmd cmd)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		if (redirect_io(in_fd, STDOUT_FILENO) == -1)
			return (1);
		if (redirect_infile(outfile) == -1)
			return (1);
		if (execve(cmd.path, cmd.cmd, NULL) == -1)
		{
				//write(STD_OUT, "Deu muito errado\n", 17);
		}
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
	return (0);
}
*/