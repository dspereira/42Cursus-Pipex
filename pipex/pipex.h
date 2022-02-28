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

typedef struct s_cmd
{
    char *path;
    char **cmd;
}   t_cmd;

typedef struct s_pipe
{
    int w_fd;
    int r_fd;
}   t_pipe;

int set_std_io(char *infile, char *outfile);

//t_cmd *get_cmds(int size, const char **cmds);
t_cmd *get_cmds(int size, const char **cmds, const char **paths);
void free_cmds(int size, t_cmd *cmds);
// Função de teste retirar no final
void print_cmd(int size, t_cmd *cmds);

char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t count, size_t size);
char *ft_strcat(char *dst, const char *src);
char	*ft_strnstr(const char *s1, const char *s2, size_t n);


int redirect_infile(const char *infile);
int redirect_io(int oldfd, int newfd);

int open_pipe(t_pipe *p);
int close_pipe(t_pipe p);

char **get_path(char **envp);
void free_path(char **m);

int exec_cmd(int in_fd, int out_fd, t_cmd cmd);

#endif