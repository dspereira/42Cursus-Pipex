#include "pipex.h"



t_cmd *get_cmds(int size, char **cmds)
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
			printf("%s ", cmds[j].cmd[k]);
			k++;
		}
		j++;
	}
}

