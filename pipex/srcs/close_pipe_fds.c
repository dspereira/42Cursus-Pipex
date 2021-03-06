/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipe_fds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:36:49 by dsilveri          #+#    #+#             */
/*   Updated: 2022/05/03 11:39:44 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	close_pipe_fds(t_fds *fds)
{
	t_fd	*fd;
	int		i;

	if (!fds)
		return ;
	fd = fds->fd;
	i = 0;
	while (i < fds->size)
	{
		if (fd[i].r >= 0)
		{
			close(fd[i].r);
			fd[i].r = -1;
		}
		if (fd[i].w >= 0)
		{
			close(fd[i].w);
			fd[i].w = -1;
		}
		i++;
	}
	if (fd)
		free(fd);
	free(fds);
	save_alloc_mem(0, TYPE_FDS);
}
