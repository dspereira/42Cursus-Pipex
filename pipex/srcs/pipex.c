#include "../includes/pipex.h"

void	exec_cmd(t_fds *fds, t_cmd cmd, t_fd fd, char **env)
{
	int	pid;

	pid = fork();
	if (!pid)
	{
		sys_error(dup2(fd.r, STDIN_FILENO));
		sys_error(dup2(fd.w, STDOUT_FILENO));
		close_fds(fds);
		if (cmd.cmd[0])
		{
			execve(cmd.path, cmd.cmd, env);
			exit(EXIT_FAILURE);
		}
		exit(0);
	}
}

void	exec_cmds(t_fds *fds, t_cmds *cmds, char **env)
{
	int 	n_cmds;
	int		i;
	t_fd	*fd;
	t_fd	actual_fd;
	t_cmd	*cmd;

	fd = fds->fd;
	cmd = cmds->cmd;
	n_cmds = cmds->size;
	i = 0;
	while (i < n_cmds)
	{
		actual_fd.r = fd[i].r;
		actual_fd.w = fd[i + 1].w;
		exec_cmd(fds, cmd[i], actual_fd, env);
		i++;
	}	
}

void	wait_cmds_end(int n_cmds)
{	
	int	i;

	i = 0;
	while (i < n_cmds)
	{
		wait(NULL);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_fds	*fds;
	t_cmds	*cmds;
	t_paths	*paths;
	int		num_cmds;
	int		size_arr_fd;

	if (argc != 5)
	{
		ft_printf("%s: Wrong number of parametersn\n", PROGRAM_NAME);
		ft_printf("Usage \"./pipex infile cmd1 cmd2 outfile\"\n");
		return (0);
	}
	num_cmds = argc - 3;
	size_arr_fd = num_cmds + 1;
	paths = get_paths(envp);
	fds = get_fds(argv[1], argv[argc - 1], size_arr_fd);
	cmds = get_cmds(num_cmds, (argv + 2), paths->paths);
	exec_cmds(fds, cmds, envp);
	close_fds(fds);
	wait_cmds_end(num_cmds);
	free_alloc_mem();
}
