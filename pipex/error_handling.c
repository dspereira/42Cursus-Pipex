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

int	file_not_found_err(int err, char *file)
{
	if (err == -1)
	{
		printf("pipex: %s: %s\n", file, strerror(errno));
		free_alloc_mem();
		exit(EXIT_FAILURE);
	}
	return (err);
}

void	cmd_not_found_err(const char *cmd_path, const char *cmd)
{
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
