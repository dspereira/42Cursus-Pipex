#include "../includes/pipex.h"

int	sys_error(int err)
{
	if (err == -1)
	{
		perror(PROGRAM_NAME);
		free_alloc_mem();
		exit(EXIT_FAILURE);
	}
	return (err);
}

int	file_not_found_err(int err, char *file)
{
	if (err == -1)
	{
		ft_printf("%s: %s: %s\n", PROGRAM_NAME, file, strerror(errno));
		free_alloc_mem();
		exit(EXIT_FAILURE);
	}
	return (err);
}

void	cmd_not_found_err(const char *cmd_path, const char *cmd)
{
	if (!cmd_path)
		ft_printf("%s: command not found: %s\n", PROGRAM_NAME, cmd);
}

void	*oom_guard(void *p)
{
	if (!p)
	{
		ft_printf("%s: Out of memory!\n", PROGRAM_NAME);
		free_alloc_mem();
		exit(EXIT_FAILURE);
	}
	return (p);
}
