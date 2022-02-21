#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct s_cmd
{
    char **cmd;
}   t_cmd;

int set_std_io(char *infile, char *outfile);

t_cmd *get_cmds(int size, char **cmds);
void free_cmds(int size, t_cmd *cmds);
// Função de teste retirar no final
void print_cmd(int size, t_cmd *cmds);

char	**ft_split(char const *s, char c);


#endif