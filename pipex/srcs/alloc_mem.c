/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogo <diogo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:36:28 by dsilveri          #+#    #+#             */
/*   Updated: 2022/05/02 20:44:24 by diogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static t_alloc_mem	*alloc_mem(void *elem, int type);

void	init_alloc_mem(void)
{
	alloc_mem(0, NO_TYPE);
}

void	save_alloc_mem(void *mem, int type)
{
	alloc_mem(mem, type);
}

void	free_alloc_mem(void)
{
	t_alloc_mem	*mem;

	mem = alloc_mem(0, NO_TYPE);
	if (mem && mem->paths)
		free_paths(mem->paths);
	if (mem && mem->cmds)
		free_cmds(mem->cmds);
	if (mem && mem->fds)
		close_pipe_fds(mem->fds);
	if (mem)
		free(mem);
}

static t_alloc_mem	*alloc_mem(void *elem, int type)
{
	static t_alloc_mem	*mem = 0;

	if (!mem)
	{
		mem = oom_guard2(malloc(sizeof(t_alloc_mem)));
		mem->cmds = 0;
		mem->fds = 0;
		mem->paths = 0;
	}
	if (type == TYPE_CMDS)
		mem->cmds = (t_cmds *) elem;
	else if (type == TYPE_FDS)
		mem->fds = (t_fds *) elem;
	else if (type == TYPE_PATHS)
		mem->paths = (t_paths *) elem;
	return (mem);
}
