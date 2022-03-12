#include "pipex.h"

#define NO_TYPE 	0
#define TYPE_CMDS 	1
#define TYPE_FDS 	2
#define TYPE_PATHS 	3

t_alloc_mem	*alloc_mem(void *elem, int type)
{
	static t_alloc_mem	*mem = 0;

	if (!mem)
	{
		mem = malloc(sizeof(t_alloc_mem));
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

void	save_alloc_paths(t_paths *paths)
{
	alloc_mem(paths, TYPE_PATHS);
}

void	save_alloc_cmds(t_cmds *cmds)
{
	alloc_mem(cmds, TYPE_CMDS);
}

void	save_alloc_fds(t_fds *fds)
{
	alloc_mem(fds, TYPE_FDS);
}

void	save_alloc_mem(t_cmds *cmds, t_fds *fds, t_paths *paths)
{
	save_alloc_cmds(cmds);
	save_alloc_paths(paths);
	save_alloc_fds(fds);
}

t_alloc_mem	*get_alloc_mem(void)
{
	return (alloc_mem(0, NO_TYPE));
}

void	free_alloc_mem(void)
{
	t_alloc_mem	*mem;

	mem = get_alloc_mem();
	if (mem && mem->paths)
		free_path(mem->paths);
	if (mem && mem->cmds)
		free_cmds(mem->cmds);
	if (mem && mem->fds)
		close_fds(mem->fds);
	if (mem)
		free(mem);
}