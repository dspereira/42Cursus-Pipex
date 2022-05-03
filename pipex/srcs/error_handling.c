/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:36:58 by dsilveri          #+#    #+#             */
/*   Updated: 2022/05/03 14:38:55 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	sys_error(int err, char *str)
{
	if (err == -1)
	{
		if (str == 0)
			perror(PROGRAM_NAME);
		else
			print_msg_error(strerror(errno), str);
		free_alloc_mem();
		exit(EXIT_FAILURE);
	}
	return (err);
}

int	file_error(int err, char *file)
{
	if (err == -1)
	{
		print_msg_error(strerror(errno), file);
		free_alloc_mem();
		exit(EXIT_FAILURE);
	}
	return (err);
}

void	cmd_not_found_error(char *cmd_path, char *cmd)
{
	if (!cmd_path)
	{
		print_msg_error("command not found", cmd);
		free_alloc_mem();
		exit(EXIT_FAILURE);
	}
}

void	*oom_guard(void *p)
{
	if (!p)
	{
		write(2, "pipex: Out of memory!\n", strlen("pipex: Out of memory!\n"));
		free_alloc_mem();
		exit(EXIT_FAILURE);
	}
	return (p);
}

void	*oom_guard2(void *p)
{
	if (!p)
	{
		write(2, "pipex: Out of memory!\n", strlen("pipex: Out of memory!\n"));
		exit(EXIT_FAILURE);
	}
	return (p);
}
