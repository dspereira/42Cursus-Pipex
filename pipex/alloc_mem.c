#include "pipex.h"

t_alloc_mem *alloc_mem(t_cmds *cmds, t_fds *fds, char **paths, int save)
{
	static t_alloc_mem *mem = 0;

	if (save)
	{
		if (mem == 0)
			mem = malloc(sizeof(t_alloc_mem));
		if (cmds)
			mem->cmds = cmds;
		if (fds)
			mem->fds = fds;
		if (paths)
			mem->paths = paths;
	}
	return (mem);
}

void save_alloc_paths(char **paths)
{
	alloc_mem(0, 0, paths, 1);
}

void save_alloc_cmds(t_cmds *cmds)
{
	alloc_mem(cmds, 0, 0, 1);
}

void save_alloc_fds(t_fds *fds)
{
	alloc_mem(0, fds, 0, 1);
}

void save_alloc_mem(t_cmds *cmds, t_fds *fds, char **paths)
{
	alloc_mem(cmds, fds, paths, 1);
}

t_alloc_mem *get_alloc_mem(void)
{
	return (alloc_mem(0, 0, 0, 0));
}

void free_alloc_mem(void)
{
	t_alloc_mem *mem;

	mem = get_alloc_mem();
	if (mem && mem->paths)
		free_path(mem->paths);
	if (mem && mem->cmds)	
		free_cmds(mem->cmds);
	if (mem && mem->fds);
		//close_fds(mem->fds);	
	if (mem)
		free(mem);
}