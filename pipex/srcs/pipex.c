/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:37:44 by dsilveri          #+#    #+#             */
/*   Updated: 2022/04/28 14:29:29 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	exec_cmd(t_fds *fds, t_cmd cmd, t_fd fd, t_files file)
{
	int	pid;

	pid = fork();
	if (!pid)
	{
		if (file.in)
			fd.r = file_error(open(file.in, O_RDONLY), file.in);
		else if (file.out)
		{
			if (access(file.out, F_OK) == 0)
			{
				file_error(access(file.out, W_OK), file.out);
				file_error(unlink(file.out), file.out);

			}
			fd.w = file_error(open(file.out, O_CREAT | O_WRONLY, 0644), file.out);
		}
		cmd_not_found_err(cmd.path, cmd.cmd[0]);
		sys_error(dup2(fd.r, STDIN_FILENO));
		sys_error(dup2(fd.w, STDOUT_FILENO));
		close_fds(fds);
		if (cmd.cmd[0])
		{
			execve(cmd.path, cmd.cmd, NULL);
			exit(EXIT_FAILURE);
		}
		exit(0);
	}
}

void	exec_cmds(t_fds *fds, t_cmds *cmds, char *infile, char *outfile)
{
	int		i;
	t_fd	fd;
	t_cmd	*cmd;
	t_files	file;
	
	cmd = cmds->cmd;
	i = 0;
	while (i < cmds->size)
	{
		fd.r = fds->fd[i].r;
		fd.w = fds->fd[i + 1].w;
		file.in = 0;
		file.out = 0;
		if (!i)
			file.in = infile;
		else if (i == cmds->size - 1)
			file.out = outfile;
		exec_cmd(fds, cmd[i], fd, file);
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

int	main(int argc, char **argv, char **envp)
{
	t_fds	*fds;
	t_cmds	*cmds;
	t_paths	*paths;
	int		num_cmds;
	int		size_arr_fd;

	if (argc < 5)
	{
		ft_printf("%s: Wrong number of parametersn\n", PROGRAM_NAME);
		ft_printf("Usage \"./pipex infile cmd1 cmd2 ... cmdn outfile\"\n");
		return (0);
	}
	num_cmds = argc - 3;
	size_arr_fd = num_cmds + 1;
	paths = get_paths(envp);
	fds = get_fds(size_arr_fd);
	cmds = get_cmds(num_cmds, (argv + 2), paths->paths);
	exec_cmds(fds, cmds, argv[1], argv[argc - 1]);
	close_fds(fds);
	wait_cmds_end(num_cmds);
	free_alloc_mem();
}
