#include "pipex.h"

t_paths *get_path(char **envp)
{
    char *path_str;
    char *word;
    t_paths *p;
    int word_size;
    int i;

    word = "PATH=";
    word_size = ft_strlen(word);
    p = malloc(sizeof(t_paths));
    i = 0;
    while (envp[i])
    {
        path_str = ft_strnstr(envp[i], word, word_size);
        if (path_str)
            p->paths = ft_split((path_str + word_size), ':');
        i++;
    }
    return (p);
}

void free_path(t_paths *paths)
{   
    int i;
    char **m;

    m = paths->paths;
    if (paths)
    {
        i = 0;
        while (m[i])
        {
            free(m[i]);
            i++;
        }
        free(m);
        free(paths);
    }
}