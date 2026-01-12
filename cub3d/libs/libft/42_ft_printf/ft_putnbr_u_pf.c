/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_u_pf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:55:14 by ruiferna          #+#    #+#             */
/*   Updated: 2025/05/06 17:16:05 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_u_pf(unsigned int n, int fd)
{
	long int	length;

	length = 0;
	if (n >= 10)
		length += ft_putnbr_u_pf(n / 10, fd);
	ft_putchar_pf((n % 10) + '0', fd);
	length++;
	return (length);
}
