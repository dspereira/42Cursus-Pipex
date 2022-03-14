#include "pipex.h"

// gcc pipex.c get_cmd.c get_path.c set_fd.c utils.c utils2.c alloc_mem.c error_handling.c 
void exec_cmd(t_fds *fds, t_cmd cmd, int i);

int main (int argc, char **argv, char **envp)
{
	int size;
	t_fds *fds;
	t_cmds *cmds;
	t_paths *paths;
	int i;
	
	size = argc - 2;
	paths = get_path(envp);
	fds = set_fd(argv[1], argv[argc - 1], size);
	cmds = get_cmds(argc - 3, (const char**)(argv + 2), (const char **)paths->paths);
	i = 0;
	while (i < argc - 3)
	{
		exec_cmd(fds, cmds->cmd[i], i);
		i++;
	}
	close_fds(fds);
	save_alloc_fds(0);
	i = 0;
	int status; 
	while (i < argc - 3)
	{
		wait(&status);
		i++;
	}
	free_alloc_mem();
}

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
