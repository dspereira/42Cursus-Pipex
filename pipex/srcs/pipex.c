/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogo <diogo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:37:44 by dsilveri          #+#    #+#             */
/*   Updated: 2022/05/04 10:06:35 by diogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void		wait_cmds_end(int num_cmds);

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	int		num_cmds;

	if (argc < 5)
	{
		ft_printf("%s: Wrong number of parameters\n", PROGRAM_NAME);
		ft_printf("Usage: \"./pipex infile cmd1 cmd2 ... cmdn outfile\"\n");
		return (0);
	}
	data.env = env;
	data.files.in = argv[1];
	data.files.out = argv[argc - 1];
	num_cmds = argc - 3;
	init_alloc_mem();
	data.paths = get_paths(env);
	data.fds = get_fds(num_cmds - 1);
	data.cmds = get_cmds(num_cmds, (argv + 2), data.paths->paths);
	exec_cmds(data);
	close_pipe_fds(data.fds);
	wait_cmds_end(num_cmds);
	free_alloc_mem();
	return (0);
}

static void	wait_cmds_end(int num_cmds)
{	
	int	i;

	i = 0;
	while (i < num_cmds)
	{
		wait(NULL);
		i++;
	}
}
