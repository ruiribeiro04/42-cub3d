/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:01:57 by ruiferna          #+#    #+#             */
/*   Updated: 2025/05/06 17:12:56 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_format(char c, va_list args)
{
	if (c == 'c')
		return (ft_putchar_pf(va_arg(args, int), 1));
	if (c == 's')
		return (ft_putstr_pf(va_arg(args, char *), 1));
	if (c == 'd' || c == 'i')
		return (ft_putnbr_pf(va_arg(args, int), 1));
	if (c == 'u')
		return (ft_putnbr_u_pf(va_arg(args, unsigned int), 1));
	if (c == 'x')
		return (ft_putnbr_hex(va_arg(args, unsigned int), "0123456789abcdef",
				1));
	if (c == 'X')
		return (ft_putnbr_hex(va_arg(args, unsigned int), "0123456789ABCDEF",
				1));
	if (c == 'p')
		return (ft_putpointer(va_arg(args, void *), 1));
	if (c == '%')
		return (ft_putchar_pf('%', 1));
	return (-1);
}

int	ft_printf(const char *str, ...)
{
	va_list	va;
	size_t	counter;

	if (!str)
		return (0);
	counter = 0;
	va_start(va, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			counter += ft_format(*str, va);
		}
		else
			counter += ft_putchar_pf(*str, 1);
		str++;
	}
	va_end(va);
	return (counter);
}
