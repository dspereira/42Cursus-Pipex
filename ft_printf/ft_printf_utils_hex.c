/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_hex.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 10:49:18 by diogo             #+#    #+#             */
/*   Updated: 2021/11/29 15:15:14 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

static char	*str_inverter(char *dst, char *src)
{
	int	i;
	int	j;

	j = 0;
	while (src[j] != '\0')
		j++;
	j--;
	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[j];
		j--;
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

/*
	return: size of number in hexadecimal
*/
static int	convert_hex(char *nb, char *conv_str, unsigned long n)
{
	char	inv_nb[20];
	int		i;

	i = 0;
	if (n == 0)
	{
		inv_nb[i] = '0';
		i++;
	}
	while (n > 0)
	{
		inv_nb[i] = conv_str[n % 16];
		n /= 16;
		i++;
	}
	inv_nb[i] = '\0';
	str_inverter(nb, inv_nb);
	return (i);
}

int	print_hexa_low(va_list args)
{
	char	nb[20];
	int		size;

	size = convert_hex(nb, HEX_LOWER, va_arg(args, unsigned int));
	write(FD, nb, size);
	return (size);
}

int	print_hexa_upp(va_list args)
{
	char	nb[20];
	int		size;

	size = convert_hex(nb, HEX_UPPER, va_arg(args, unsigned int));
	write(FD, nb, size);
	return (size);
}

int	print_ptr(va_list args)
{
	char	nb[20];
	int		size;

	size = convert_hex(nb, HEX_LOWER, va_arg(args, unsigned long));
	if (nb[0] != '0')
	{
		write(FD, "0x", 2);
		write(FD, nb, size);
		return (size + 2);
	}
	else
	{
		write(FD, "0x0", 3);
		return (3);
	}
}
