/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogo <diogo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:37:44 by dsilveri          #+#    #+#             */
/*   Updated: 2022/05/01 19:44:33 by diogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	wait_cmds_end(int num_cmds);

t_cmd get_command(t_data data, int i)
{
	t_cmd cmd;

	cmd = data.cmds->cmd[i];
	cmd_not_found_error(cmd.path, cmd.cmd[0]);
	return (cmd);
}

t_fd get_fds_to_exec(t_data data, int i)
{
	t_files	file;
	t_fd	fd;
	int		n_cmds;

	file = data.files;
	n_cmds = data.cmds->size;
	fd.r = -1;
	fd.w = -1;
	if (!i)
		fd.r = file_error(open(file.in, O_RDONLY), file.in);
	else if (i == n_cmds - 1)
	{
		if (access(file.out, F_OK) == 0)
		{
			file_error(access(file.out, W_OK), file.out);
			file_error(unlink(file.out), file.out);
		}
		fd.w = file_error(open(file.out, O_CREAT | O_WRONLY, 00644), file.out);		
	}
	if (fd.r == -1)
		fd.r = data.fds->fd[i - 1].r;
	if (fd.w == -1)
		fd.w = data.fds->fd[i].w;
	return (fd);		
}

void make_redirection(t_fds *all_fds, t_fd fd)
{
	sys_error(dup2(fd.r, STDIN_FILENO));
	sys_error(dup2(fd.w, STDOUT_FILENO));
	close_fds(all_fds);
}

void	exec_fork(t_data data, int i)
{
	int	pid;
	t_cmd cmd;
	t_fd fd;

	pid = fork();
	if (!pid)
	{
		fd = get_fds_to_exec(data, i);
		cmd = get_command(data, i);
		make_redirection(data.fds, fd);
		sys_error(execve(cmd.path, cmd.cmd, data.env));
		exit(0);
	}
}

void	exec_cmds(t_data data)
{
	t_fd fd;
	t_cmds *cmds;
	t_files	files;
	int i;

	cmds = data.cmds;
	i = 0;
	while (i < cmds->size)
	{
		exec_fork(data, i);
		i++;
	}
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

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	int		num_cmds;

	if (argc < 5)
	{
		ft_printf("%s: Wrong number of parametersn\n", PROGRAM_NAME);
		ft_printf("Usage \"./pipex infile cmd1 cmd2 ... cmdn outfile\"\n");
		return (0);
	}
	data.env = env;
	data.files.in = argv[1];
	data.files.out = argv[argc - 1];
	num_cmds = argc - 3;
	data.paths = get_paths(env);
	data.fds = get_fds(num_cmds - 1);
	data.cmds = get_cmds(num_cmds, (argv + 2), data.paths->paths);
	exec_cmds(data);
	close_fds(data.fds);
	wait_cmds_end(num_cmds);
	free_alloc_mem();
}
