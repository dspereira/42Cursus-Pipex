/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogo <diogo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:36:58 by dsilveri          #+#    #+#             */
/*   Updated: 2022/04/29 20:11:30 by diogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	sys_error(int err)
{
	if (err == -1)
	{
		perror(PROGRAM_NAME);
		free_alloc_mem();
		exit(EXIT_FAILURE);
	}
	return (err);
}

int	file_error(int err, char *file)
{
	if (err == -1)
	{
		ft_printf("%s: %s: %s\n", PROGRAM_NAME, file, strerror(errno));
		free_alloc_mem();
		exit(EXIT_FAILURE);
	}
	return (err);
}

void	cmd_not_found_error(const char *cmd_path, const char *cmd)
{
	if (!cmd_path)
	{
		ft_printf("%s: command not found: %s\n", PROGRAM_NAME, cmd);
		free_alloc_mem();
		exit(EXIT_FAILURE);
	}
}

void	*oom_guard(void *p)
{
	if (!p)
	{
		ft_printf("%s: Out of memory!\n", PROGRAM_NAME);
		free_alloc_mem();
		exit(EXIT_FAILURE);
	}
	return (p);
}
