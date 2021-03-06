/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogo <diogo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:37:28 by dsilveri          #+#    #+#             */
/*   Updated: 2022/05/02 20:33:04 by diogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static t_fds	*init_fds(void);
static t_fd		*init_fd(int num_fd);
static void		create_pipes(t_fd *fd, int size);

t_fds	*get_fds(int size)
{
	t_fds	*fds;
	t_fd	*fd;

	fds = init_fds();
	save_alloc_mem(fds, TYPE_FDS);
	fds->fd = init_fd(size);
	fds->size = size;
	fd = fds->fd;
	create_pipes(fd, size);
	return (fds);
}

static t_fds	*init_fds(void)
{
	t_fds	*fds;

	fds = oom_guard(malloc(sizeof(t_fds)));
	fds->fd = 0;
	fds->size = 0;
	return (fds);
}

static t_fd	*init_fd(int num_fd)
{
	t_fd	*fd;
	int		i;

	fd = oom_guard(malloc(num_fd * sizeof(t_fd)));
	i = 0;
	while (i < num_fd)
	{
		fd[i].r = -1;
		fd[i].w = -1;
		i++;
	}
	return (fd);
}

static void	create_pipes(t_fd *fd, int size)
{
	int	i;
	int	fd_p[2];

	i = 0;
	while (i < size)
	{
		sys_error(pipe(fd_p), 0);
		fd[i].r = fd_p[0];
		fd[i].w = fd_p[1];
		i++;
	}
}
