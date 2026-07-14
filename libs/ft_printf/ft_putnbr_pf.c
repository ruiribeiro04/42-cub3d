/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_pf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:43:39 by ruiferna          #+#    #+#             */
/*   Updated: 2025/05/06 17:18:01 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_pf(int n, int fd)
{
	long int	length;

	length = 0;
	if (n == -2147483648)
		return (ft_putstr_pf("-2147483648", 1));
	if (n < 0)
	{
		n = -n;
		length += ft_putchar_pf('-', 1);
	}
	if (n >= 10)
		length += ft_putnbr_u_pf(n / 10, fd);
	ft_putchar_pf((n % 10) + '0', fd);
	length++;
	return (length);
}
