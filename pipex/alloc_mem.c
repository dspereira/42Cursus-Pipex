#include "pipex.h"

t_alloc_mem *alloc_mem(t_cmd *cmds, char **paths, int save)
{
	static t_alloc_mem *mem = 0;

	if (save && cmds && paths)
	{
		if (mem == 0)
		{
			mem = malloc(sizeof(t_alloc_mem));
			mem->cmds = cmds;
			mem->paths = paths;
		}
	}
	return (mem);
}

void save_alloc_mem(t_cmd *cmds, char **paths)
{
	alloc_mem(cmds, paths, 1);
}

void free_alloc_mem(void)
{
	t_alloc_mem *mem;

	mem = alloc_mem(0, 0, 0);
	if (mem && mem->paths)
		free_path(mem->paths);
	if (mem && mem->cmds)	
		free_cmds(2, mem->cmds);
	if (mem)
		free(mem);
}