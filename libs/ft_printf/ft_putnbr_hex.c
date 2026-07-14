/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:50:55 by ruiferna          #+#    #+#             */
/*   Updated: 2025/05/06 17:18:13 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_hex(unsigned long n, char *hex, int fd)
{
	long int	length;

	length = 0;
	if (n >= 16)
		length += ft_putnbr_hex(n / 16, hex, fd);
	ft_putchar_pf(hex[n % 16], fd);
	length++;
	return (length);
}
