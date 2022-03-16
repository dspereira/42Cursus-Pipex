#include "pipex.h"

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

void	free_cmds(t_cmds *cmds)
{
	t_cmd	*cmd;
	int		i;

	if (!cmds)
		return ;
	cmd = cmds->cmd;
	if (cmd)
	{
		i = 0;
		while (i < cmds->size)
		{
			if (cmd[i].cmd)
				free_cmd(cmd[i].cmd);
			if (cmd[i].path)
				free(cmd[i].path);
			i++;
		}
		free(cmd);
	}
	free(cmds);
}
