/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:39:55 by diogo             #+#    #+#             */
/*   Updated: 2022/05/03 14:41:23 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static t_cmd	get_command(t_data data, int i);
static t_fd		get_fds_to_exec(t_data data, int i);
static void		make_redirection(t_data data, t_fd fd, int i);
static void		exec_fork(t_data data, int i);

void	exec_cmds(t_data data)
{
	int	i;

	i = 0;
	while (i < data.cmds->size)
	{
		exec_fork(data, i);
		i++;
	}
}

static t_cmd	get_command(t_data data, int i)
{
	t_cmd	cmd;

	cmd = data.cmds->cmd[i];
	cmd_not_found_error(cmd.path, cmd.cmd[0]);
	return (cmd);
}

static t_fd	get_fds_to_exec(t_data data, int i)
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
		fd.w = file_error(open(file.out, O_CREAT | O_WRONLY | O_TRUNC, 0644),
				file.out);
	if (fd.r == -1)
		fd.r = data.fds->fd[i - 1].r;
	if (fd.w == -1)
		fd.w = data.fds->fd[i].w;
	return (fd);
}

static void	make_redirection(t_data data, t_fd fd, int i)
{
	sys_error(dup2(fd.r, STDIN_FILENO), 0);
	sys_error(dup2(fd.w, STDOUT_FILENO), 0);
	if (!i)
		close(fd.r);
	else if (i == data.cmds->size - 1)
		close(fd.w);
	close_pipe_fds(data.fds);
}

static void	exec_fork(t_data data, int i)
{
	int		pid;
	t_cmd	cmd;
	t_fd	fd;

	pid = fork();
	if (!pid)
	{
		fd = get_fds_to_exec(data, i);
		cmd = get_command(data, i);
		make_redirection(data, fd, i);
		sys_error(execve(cmd.path, cmd.cmd, data.env), cmd.cmd[0]);
		exit(0);
	}
}
