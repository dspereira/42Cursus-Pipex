#include "pipex.h"

char *get_cmd_path(const char *cmd)
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

t_cmd *get_cmds(int size, const char **cmds)
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
		i++;
	}
	cmd[0].path = get_cmd_path(cmd[0].cmd[0]);
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
