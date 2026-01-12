/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_pf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:42:28 by ruiferna          #+#    #+#             */
/*   Updated: 2025/05/06 17:17:46 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_pf(char *s, int fd)
{
	int	i;

	if (!s)
		return (ft_putstr_pf("(null)", fd));
	i = 0;
	while (s[i] != '\0')
	{
		if (ft_putchar_pf(s[i], fd) < 0)
			return (-1);
		i++;
	}
	return (i);
}
