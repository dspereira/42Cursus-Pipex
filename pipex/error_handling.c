#include "pipex.h"

int	sys_error(int err)
{
	if (err == -1)
	{
		perror("pipex");
		free_alloc_mem();
		exit(EXIT_FAILURE);
	}
	return (err);
}

void	cmd_not_found_err(const char *cmd_path, const char *cmd)
{
	// alterar pela ft_printf 
	if (!cmd_path)
		printf("pipex: command not found: %s\n", cmd);
}

void	*oom_guard(void *p)
{
	if (!p)
	{
		printf("pipex: Out of memory!\n");
		free_alloc_mem();
		exit(EXIT_FAILURE);
	}
	return (p);
}
