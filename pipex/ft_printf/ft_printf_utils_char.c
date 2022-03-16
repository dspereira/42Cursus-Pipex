/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_char.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 10:45:53 by diogo             #+#    #+#             */
/*   Updated: 2021/11/29 15:28:30 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

int	print_char(va_list args)
{
	int	c;

	c = va_arg(args, int);
	write(FD, &c, 1);
	return (1);
}

int	print_string(va_list args)
{
	char	*s;
	int		i;

	s = va_arg(args, char *);
	if (!s)
	{
		write(FD, "(null)", 6);
		return (6);
	}
	i = 0;
	while (s[i] != '\0')
	{
		write(FD, &(s[i]), 1);
		i++;
	}
	return (i);
}

int	print_percent(void)
{
	write(FD, "%", 1);
	return (1);
}
