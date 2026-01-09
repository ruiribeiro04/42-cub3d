/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-maga <vde-maga@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:15:19 by vde-maga          #+#    #+#             */
/*   Updated: 2025/04/23 16:45:44 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
//#include <stdio.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = s;
	i = 0;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (str);
}
/*
int	main(void)
{
	char	buffer[50];
	int		value;
	size_t	n;

	value = '*';
	n = 5;
	ft_memset(buffer, value, n);
	buffer[n] = '\0';
	printf("Buffer após ft_memset: %s\n", buffer);
	return (0);
}
*/
