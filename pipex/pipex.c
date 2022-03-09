#include "pipex.h"

// gcc pipex.c get_cmd.c pipe.c get_path.c exec_cmd.c set_fd.c utils.c utils2.c alloc_mem.c

int main (int argc, char **argv, char **envp)
{
	 int size;
	 t_fds fds;
	 t_cmd *cmds;
	 char **paths;
	 int i;

	 size = argc - 2;
	 paths = get_path(envp);
	 cmds = get_cmds(argc - 3, (const char**)(argv + 2), (const char **)paths);
	 fds = set_fd(argv[1], argv[argc - 1], size);
	 save_alloc_mem(cmds, paths);

	 i = 0;
	 while (i < argc - 3)
	 {
		 exec_cmd(fds, cmds[i], i);
		 i++;
	 }
	 close_fds(fds);
	 i = 0;
	 int status; 
	 while (i < argc - 3)
	 {
		 wait(&status);
		 if (status)
		 {
			 printf("porque!\n");
			 exit(1);
		 }
		 i++;
	 }
	 free_alloc_mem();
}

