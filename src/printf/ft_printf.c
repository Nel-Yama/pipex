/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nel-yama@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 00:54:55 by nel-yama          #+#    #+#             */
/*   Updated: 2025/04/24 00:54:55 by nel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	parse_format(const char *format, va_list *args)
{
	int	i;

	i = 0;
	if (format[0] == '%' && (format[1] == 'd' || format[1] == 'i'))
		i += ft_putnbr_base(va_arg(*args, int), "0123456789", 1);
	else if (format[0] == '%' && format[1] == 'c')
		i += ft_putchar_fd(va_arg(*args, int), 1);
	else if (format[0] == '%' && format[1] == 's')
		i += ft_putstr_fd(va_arg(*args, char *), 1);
	else if (format[0] == '%' && format[1] == 'u')
		i += ft_put_unsigned_nbr(va_arg(*args, unsigned int), 1);
	else if (format[0] == '%' && format[1] == 'p')
		i += ft_put_ptr(va_arg(*args, void *), 1);
	else if (format[0] == '%' && format[1] == 'x')
		i += ft_put_unsigned_nbr_base(va_arg(*args, unsigned int),
				"0123456789abcdef", 1);
	else if (format[0] == '%' && format[1] == 'X')
		i += ft_put_unsigned_nbr_base(va_arg(*args,
					unsigned int), "0123456789ABCDEF", 1);
	else if (format[0] == '%' && format[1] == '%')
		i += ft_putchar_fd('%', 1);
	else
		i += ft_putchar_fd(format[1], 1);
	return (i);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	size_t	i;

	if (!format || !(*format))
		return (0);
	va_start(args, format);
	i = 0;
	while (*format)
	{
		if (*format != '%')
		{
			ft_putchar_fd(*format, 1);
			format++;
			i++;
		}
		else
		{
			i += parse_format(format, &args);
			format += 2;
		}
	}
	va_end(args);
	return (i);
}
/*
#include <stdio.h>

int main()
{
    int n = -2147483647;
    printf("%%i  : |%i|\n", n);
    printf("%%d  : |%d|\n", n);
    printf("%%u  : |%u|\n", n);
    unsigned int un= (unsigned int)n;
    printf("%%un : |%u|\n", un);
    return 0;
}
*/
