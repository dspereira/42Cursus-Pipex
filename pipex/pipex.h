#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define CMDS_PATH "/usr/bin/"

typedef struct s_cmd
{
    char *path;
    char **cmd;
}   t_cmd;

int set_std_io(char *infile, char *outfile);

t_cmd *get_cmds(int size, const char **cmds);
void free_cmds(int size, t_cmd *cmds);
// Função de teste retirar no final
void print_cmd(int size, t_cmd *cmds);

char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t count, size_t size);
char *ft_strcat(char *dst, const char *src);


#endif