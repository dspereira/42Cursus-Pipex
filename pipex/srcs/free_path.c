#include "pipex.h"

void	free_paths(t_paths *paths)
{
	int		i;
	char	**m;

	if (!paths)
		return ;
	m = paths->paths;
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
	free(paths);
}
