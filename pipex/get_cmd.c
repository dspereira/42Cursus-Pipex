#include "pipex.h"

char *get_cmd_path1(const char *cmd)
{
	char *path;
	int size;

	size = ft_strlen(CMDS_PATH);
	size += ft_strlen(cmd);
	path = ft_calloc(size + 1, sizeof(char));
	ft_strcat(path, CMDS_PATH);
	ft_strcat(path, cmd);
	return (path);
}

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
	return (path);
}

t_cmd *get_cmds(int size, const char **cmds, const char **paths)
{
	t_cmd *cmd;
	int i;

	cmd = malloc(size * sizeof(t_cmd));
	if (!cmd)
		return (0);
	i = 0;
	while (i < size)
	{
		cmd[i].cmd = ft_split(cmds[i], ' ');
		cmd[i].path = get_cmd_path(cmd[i].cmd[0], paths);
		i++;
	}
	return (cmd);
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

void free_cmds(int size, t_cmd *cmds)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free_cmd(cmds[i].cmd);
		free(cmds[i].path);
		i++;
	}
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
