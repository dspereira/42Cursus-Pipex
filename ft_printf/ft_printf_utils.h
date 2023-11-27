/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 10:33:51 by diogo             #+#    #+#             */
/*   Updated: 2021/11/29 15:13:10 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_UTILS_H
# define FT_PRINTF_UTILS_H

# include <stdarg.h>
# include <unistd.h>

# define HEX_UPPER "0123456789ABCDEF"
# define HEX_LOWER "0123456789abcdef" 
# define SIZE 9
# define FD 1

typedef struct s_format_spec
{
	char	specifier;
	int		(*func)();
}	t_format_spec;

void	fill_specifiers_arr(t_format_spec *data);
int		print_char(va_list args);
int		print_string(va_list args);
int		print_number(va_list args);
int		print_percent(void);
int		print_unsigned_int(va_list args);
int		print_hexa_low(va_list args);
int		print_hexa_upp(va_list args);
int		print_ptr(va_list args);

#endif