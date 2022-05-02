/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogo <diogo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:37:04 by dsilveri          #+#    #+#             */
/*   Updated: 2022/05/02 20:34:16 by diogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	free_cmd(char **cmd);

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

static void	free_cmd(char **cmd)
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
