#include "pipex.h"

// gcc pipex.c get_cmd.c get_path.c set_fd.c utils.c utils2.c alloc_mem.c error_handling.c 
//void	exec_cmd(t_fds *fds, t_cmd cmd, int i);
//void	exec_cmds(t_fds *fds, t_cmds *cmds, int num_cmds);

void	exec_cmd(t_fds *fds, t_cmd cmd, int r_fd, int w_fd);
void	wait_cmds_end(int num_cmds);
void	exec_cmds(t_fds *fds, t_cmds *cmds, int num_cmds);

int	main(int argc, char **argv, char **envp)
{
	t_fds	*fds;
	t_cmds	*cmds;
	t_paths	*paths;
	int		num_cmds;
	int		size_arr_fd;

	num_cmds = argc - 3;
	size_arr_fd = num_cmds + 1;
	paths = get_path(envp);
	fds = set_fd(argv[1], argv[argc - 1], size_arr_fd);
	cmds = get_cmds(num_cmds, (argv + 2), paths->paths);
	exec_cmds(fds, cmds, num_cmds);
	close_fds(fds);
	save_alloc_fds(0); // para tirar daqui
	wait_cmds_end(num_cmds);
	free_alloc_mem();
}

void	wait_cmds_end(int num_cmds)
{	
	int	i;

	i = 0;
	while (i < num_cmds)
	{
		wait(NULL);
		i++;
	}
}

void	exec_cmds(t_fds *fds, t_cmds *cmds, int num_cmds)
{
	int		i;
	t_fd	*fd;
	t_cmd	*cmd;

	fd = fds->fd;
	cmd = cmds->cmd;
	i = 0;
	while (i < num_cmds)
	{
		exec_cmd(fds, cmd[i], fd[i].r, fd[i + 1].w);
		i++;
	}	
}

void	exec_cmd(t_fds *fds, t_cmd cmd, int r_fd, int w_fd)
{
	int	pid;

	pid = fork();
	if (!pid)
	{
		sys_error(dup2(r_fd, STDIN_FILENO));
		sys_error(dup2(w_fd, STDOUT_FILENO));
		close_fds(fds);
		if (cmd.cmd[0])
		{
			execve(cmd.path, cmd.cmd, NULL);
			exit(EXIT_FAILURE);
		}
		exit(0);
	}
}
