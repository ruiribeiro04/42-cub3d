/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:59:38 by ruiferna          #+#    #+#             */
/*   Updated: 2025/05/06 17:18:23 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putpointer(void *pointer, int fd)
{
	unsigned int	length;

	if (!pointer)
		return (ft_putstr_pf("(nil)", fd));
	length = 0;
	length += ft_putstr_pf("0x", 1);
	length += ft_putnbr_hex((unsigned long)pointer, "0123456789abcdef", 1);
	return (length);
}
