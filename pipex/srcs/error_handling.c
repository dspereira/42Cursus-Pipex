/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogo <diogo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:36:58 by dsilveri          #+#    #+#             */
/*   Updated: 2022/05/01 21:41:55 by diogo            ###   ########.fr       */
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
	int msg_size;
	char *msg;
	
	if (err == -1)
	{
		msg_size = 6;
		msg_size += ft_strlen(PROGRAM_NAME);
		msg_size += ft_strlen(strerror(errno));
		msg_size += ft_strlen(file);
		msg = oom_guard(ft_calloc(msg_size, sizeof(char)));
		ft_strcat(msg, PROGRAM_NAME);
		ft_strcat(msg, ": ");
		ft_strcat(msg, strerror(errno));
		ft_strcat(msg, ": ");
		ft_strcat(msg, file);
		ft_strcat(msg, "\n");
		write(2, msg, msg_size);
		free(msg);
		free_alloc_mem();
		exit(EXIT_FAILURE);
	}
	return (err);
}

void	cmd_not_found_error(const char *cmd_path, const char *cmd)
{
	int msg_size;
	char *msg;

	if (!cmd_path)
	{
		msg_size = 2;
		msg_size += ft_strlen(PROGRAM_NAME);
		msg_size += ft_strlen(": command not found: ");
		msg_size += ft_strlen(cmd);
		msg = oom_guard(ft_calloc(msg_size, sizeof(char)));
		ft_strcat(msg, PROGRAM_NAME);
		ft_strcat(msg, ": command not found: ");
		ft_strcat(msg, cmd);
		ft_strcat(msg, "\n");
		write(2, msg, msg_size);
		free(msg);
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

void	*oom_guard2(void *p)
{
	if (!p)
	{
		ft_printf("%s: Out of memory!\n", PROGRAM_NAME);
		exit(EXIT_FAILURE);
	}
	return (p);
}
