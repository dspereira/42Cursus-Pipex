#include "pipex.h"

void exec_cmd(t_fds *fds, t_cmd cmd, int i)
{
	int pid;

	pid = fork();
	if (!pid)
	{
		sys_error(dup2(fds->fd[i].r, STDIN_FILENO));
		sys_error(dup2(fds->fd[i+1].w, STDOUT_FILENO));
		close_fds(fds);
		sys_error(execve(cmd.path, cmd.cmd, NULL));
		exit(1);
	}
}