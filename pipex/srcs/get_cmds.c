/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogo <diogo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:37:21 by dsilveri          #+#    #+#             */
/*   Updated: 2022/05/04 13:01:08 by diogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static t_cmds	*init_cmds(void);
static t_cmd	*init_cmd(int num_cmds);
static int		is_cmd_path(char *cmd);
static char		*get_cmd_path(char *cmd, char **paths);

t_cmds	*get_cmds(int size, char **m_cmd, char **paths)
{
	t_cmds	*cmds;
	t_cmd	*cmd;
	int		i;

	cmds = init_cmds();
	save_alloc_mem(cmds, TYPE_CMDS);
	cmds->cmd = init_cmd(size);
	cmds->size = size;
	cmd = cmds->cmd;
	i = 0;
	while (i < size)
	{
		cmd[i].cmd = oom_guard(ft_split(m_cmd[i], ' '));
		if (paths && cmd[i].cmd[0])
			cmd[i].path = get_cmd_path(cmd[i].cmd[0], paths);
		else
			cmd[i].path = 0;
		i++;
	}
	return (cmds);
}

static t_cmds	*init_cmds(void)
{
	t_cmds	*cmds;

	cmds = oom_guard(malloc(sizeof(t_cmds)));
	cmds->size = 0;
	cmds->cmd = 0;
	return (cmds);
}

static t_cmd	*init_cmd(int num_cmds)
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

static int	is_cmd_path(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

static char	*get_cmd_path(char *cmd, char **paths)
{
	char	*path;
	int		size;
	int		i;

	i = 0;
	while (paths[i])
	{
		size = ft_strlen(paths[i]) + ft_strlen(cmd) + 1;
		path = oom_guard(ft_calloc(size + 1, sizeof(char)));
		if (is_cmd_path(cmd))
			ft_strcat(path, cmd);
		else
		{
			ft_strcat(path, paths[i]);
			ft_strcat(path, "/");
			ft_strcat(path, cmd);
		}
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		else
			free(path);
		i++;
	}
	return (0);
}
