#include "pipex.h"

char **get_path(char **envp)
{
    char *path_str;
    char *word;
    char **paths;
    int word_size;
    int i;

    word = "PATH=";
    word_size = ft_strlen(word);
    paths = 0;
    i = 0;
    while (envp[i])
    {
        path_str = ft_strnstr(envp[i], word, word_size);
        if (path_str)
            paths = ft_split((path_str + word_size), ':');
        i++;
    }
    return (paths);
}

void free_path(char **m)
{   
    int i;

    if (m)
    {
        i = 0;
        while (m[i])
        {
            free(m[i]);
            i++;
        }
        free(m);
    }
}
