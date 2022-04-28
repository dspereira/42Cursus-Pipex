/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:37:21 by dsilveri          #+#    #+#             */
/*   Updated: 2022/04/28 11:17:39 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

t_cmds	*init_cmds(void)
{
	t_cmds	*cmds;

	cmds = oom_guard(malloc(sizeof(t_cmds)));
	cmds->size = 0;
	cmds->cmd = 0;
	return (cmds);
}

t_cmd	*init_cmd(int num_cmds)
{
	t_cmd	*cmd;
	int		i;

	cmd = oom_guard(malloc(num_cmds * sizeof(t_cmd)));
	i = 0;
	while (i < num_cmds)
	{
		cmd[i].path = 0;
		cmd[i].cmd = 0;
		i++;
	}
	return (cmd);
}

char	*get_cmd_path(char *cmd, char **paths)
{
	char	*path;
	int		size;
	int		i;

	i = 0;
	while (paths[i])
	{
		size = ft_strlen(paths[i]) + ft_strlen(cmd) + 1;
		path = oom_guard(ft_calloc(size + 1, sizeof(char)));
		ft_strcat(path, paths[i]);
		ft_strcat(path, "/");
		if (cmd)
			ft_strcat(path, cmd);
		else
			ft_strcat(path, " ");
		if (access(path, F_OK | X_OK) == 0)
			break ;
		else
		{
			free(path);
			path = 0;
		}	
		i++;
	}
	return (path);
}

t_cmds	*get_cmds(int size, char **m_cmd, char **paths)
{
	t_cmds	*cmds;
	t_cmd	*cmd;
	int		i;

	cmds = init_cmds();
	save_alloc_cmds(cmds);
	cmds->cmd = init_cmd(size);
	cmds->size = size;
	cmd = cmds->cmd;
	i = 0;
	while (i < size)
	{
		cmd[i].cmd = oom_guard(ft_split(m_cmd[i], ' '));
		if (paths)
			cmd[i].path = get_cmd_path(cmd[i].cmd[0], paths);
		else
			cmd[i].path = 0;
		//cmd_not_found_err(cmd[i].path, cmd[i].cmd[0]);
		i++;
	}
	return (cmds);
}
