#include "pipex.h"

// gcc pipex.c get_cmd.c get_path.c exec_cmd.c set_fd.c utils.c utils2.c alloc_mem.c error_handling.c 

int main (int argc, char **argv, char **envp)
{
	int size;
	t_fds *fds = 0;
	t_cmds *cmds = 0;
	t_paths *paths = 0;
	int i;
	
	size = argc - 2;
	paths = get_path(envp);
	cmds = get_cmds(argc - 3, (const char**)(argv + 2), (const char **)paths->paths);
	fds = set_fd(argv[1], argv[argc - 1], size);
	
	i = 0;
	while (i < argc - 3)
	{
		exec_cmd(fds, cmds->cmd[i], i);
		i++;
	}
	close_fds(fds);
	save_alloc_fds(0);

	i = 0;
	int status; 
	while (i < argc - 3)
	{
		wait(&status);
		if (status)
		{
			printf("porque!\n");
			free_alloc_mem();
			exit(1);
		}
		i++;
	}
	free_alloc_mem();
}

