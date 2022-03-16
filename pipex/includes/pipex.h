#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include "../ft_printf/ft_printf.h"

# define PROGRAM_NAME "pipex"

typedef struct s_cmd
{
	char	*path;
	char	**cmd;
}	t_cmd;

typedef struct s_cmds
{
	int		size;
	t_cmd	*cmd;
}	t_cmds;

typedef struct s_fd
{
	int	w;
	int	r;
}	t_fd;

typedef struct s_fds
{
	int		size;
	t_fd	*fd;
}	t_fds;

typedef struct s_paths
{
	char	**paths;
}	t_paths;

typedef struct s_alloc_mem
{
	t_cmds	*cmds;
	t_fds	*fds;
	t_paths	*paths;
}	t_alloc_mem;

/* get_cmds.c */
t_cmds	*get_cmds(int size, char **cmds, char **paths);

/* free_cmds.c */
void	free_cmds(t_cmds *cmds);

/* get_path.c */
t_paths	*get_paths(char **envp);

/* free_path.c */
void	free_paths(t_paths *paths);

/* get_fds.c */
t_fds	*get_fds(char *infile, char *outfile, int size);

/* close_fds.c */
void	close_fds(t_fds *fds);

/* utils.h */
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);

/* utils2.h */
void	*ft_calloc(size_t count, size_t size);
char	*ft_strcat(char *dst, const char *src);
char	*ft_strnstr(const char *s1, const char *s2, size_t n);

/* error_handling.c */
int		sys_error(int err);
int		file_not_found_err(int err, char *file);
void	cmd_not_found_err(const char *cmd_path, const char *cmd);
void	*oom_guard(void *p);

/* alloc_mem.c */
void	save_alloc_paths(t_paths *paths);
void	save_alloc_cmds(t_cmds *cmds);
void	save_alloc_fds(t_fds *fds);
void	free_alloc_mem(void);

#endif