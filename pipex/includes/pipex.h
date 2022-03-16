#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

//#define CMDS_PATH "/usr/bin/"
#define CMDS_PATH "/bin/"
#define PROGRAM_NAME "pipex"

typedef struct s_cmd
{
    char *path;
    char **cmd;
}   t_cmd;

typedef struct s_cmds
{
    int size;
    t_cmd *cmd;
}   t_cmds;

typedef struct s_fd
{
    int w;
    int r;
}   t_fd;

typedef struct s_fds
{
    int size;
    t_fd *fd;
}   t_fds;

typedef struct s_paths
{
    char **paths;
} t_paths;

typedef struct s_alloc_mem
{
    t_cmds  *cmds;
    t_fds   *fds;
    t_paths *paths;
}   t_alloc_mem;

int set_std_io(char *infile, char *outfile);

//t_cmd *get_cmds(int size, const char **cmds);
t_cmds *get_cmds(int size, char **cmds, char **paths);
void free_cmds(t_cmds *cmds);
// Função de teste retirar no final
void print_cmd(int size, t_cmd *cmds);


int redirect_infile(const char *infile);
int redirect_io(int oldfd, int newfd);

//char **get_path(char **envp);
t_paths *get_path(char **envp);
//void free_path(char **m);
void free_path(t_paths *paths);


/* pipe.c */
int open_pipe(t_fd *p);
// Não á necessidade desta função rever
//int close_fd(int *fd);
void close_fds(t_fds *fds);

/* utils.h */
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);

/* utils2.h */
void	*ft_calloc(size_t count, size_t size);
char *ft_strcat(char *dst, const char *src);
char	*ft_strnstr(const char *s1, const char *s2, size_t n);


//t_fd *set_fd(char *infile, char *outfile, int size);
//t_fds *set_fd(char *infile, char *outfile, int size);
t_fds	*get_fds(char *infile, char *outfile, int size);
//int close_fds(t_fds *fds);

//void exec_cmd(t_fds fds, t_cmd cmd, int i);
//void exec_cmd(t_fds *fds, t_cmd cmd, int i);

int sys_error(int err);
void cmd_not_found_err(const char *cmd_path, const char *cmd);
void	*oom_guard(void *p);
int	file_not_found_err(int err, char *file);

/* alloc_mem.c */
void free_alloc_mem(void);

//void save_alloc_paths(char **paths);
void save_alloc_paths(t_paths *paths);
void save_alloc_cmds(t_cmds *cmds);
void save_alloc_fds(t_fds *fds);
//void save_alloc_mem(t_cmds *cmds, char **paths);
//void save_alloc_mem(t_cmds *cmds, t_fds *fds, char **paths);
void save_alloc_mem(t_cmds *cmds, t_fds *fds, t_paths *paths);

#endif