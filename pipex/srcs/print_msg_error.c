/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:16:25 by dsilveri          #+#    #+#             */
/*   Updated: 2022/05/03 12:35:36 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	print_msg_error(char *error, char *str)
{
	int		msg_size;
	char	*msg;

	msg_size = 6;
	msg_size += ft_strlen(PROGRAM_NAME);
	msg_size += ft_strlen(error);
	msg_size += ft_strlen(str);
	msg = oom_guard(ft_calloc(msg_size, sizeof(char)));
	ft_strcat(msg, PROGRAM_NAME);
	ft_strcat(msg, ": ");
	ft_strcat(msg, error);
	ft_strcat(msg, ": ");
	ft_strcat(msg, str);
	ft_strcat(msg, "\n");
	write(2, msg, msg_size);
	free(msg);
}
