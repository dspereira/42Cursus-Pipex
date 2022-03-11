#include "pipex.h"

char *get_cmd_path(const char *cmd, const char **paths)
{
	char *path;
	int size;
	int i;

	i = 0;
	while (paths[i])
	{
		size = ft_strlen(paths[i]) + ft_strlen(cmd) + 1;
		path = ft_calloc(size + 1, sizeof(char));
		if (!path)
			return (0);
		ft_strcat(path, paths[i]);
		ft_strcat(path, "/");
		ft_strcat(path, cmd);
		if (access(path, X_OK) == 0)
			break;
		else
		{
			free(path);
			path = NULL;
		} 	
		i++;
	}
	cmd_not_found_err(path, cmd);
	return (path);
}

/*
	size: num cmd
*/
t_cmds *get_cmds(int size, const char **m_cmd, const char **paths)
{
	t_cmds *cmds;
	int i;

	
	cmds = malloc(sizeof(t_cmds));
	cmds->cmd = malloc(size * sizeof(t_cmd));
	cmds->size = size;
	i = 0;
	while (i < size)
	{
		cmds->cmd[i].cmd = ft_split(m_cmd[i], ' ');
		cmds->cmd[i].path = get_cmd_path(cmds->cmd[i].cmd[0], paths);
		i++;
	}
	return (cmds);
}

void	free_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

void free_cmds(t_cmds *cmds)
{
	t_cmd *cmd;
	int	i;

	cmd = cmds->cmd;
	i = 0;
	while (i < cmds->size)
	{
		free_cmd(cmd[i].cmd);
		free(cmd[i].path);
		i++;
	}
	free(cmd);
	free(cmds);
}

// Função de teste retirar no final
void print_cmd(int size, t_cmd *cmds)
{
	int j = 0;
	int k;
	while (j < size)
	{
		printf("\ncmd: ");
		k = 0;
		while (cmds[j].cmd[k])
		{
			printf("%s \n", cmds[j].cmd[k]);
			k++;
		}
		j++;
	}
}
