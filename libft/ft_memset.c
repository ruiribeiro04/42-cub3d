/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:12:28 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/05 15:11:13 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int value, size_t num)
{
	unsigned char	*p;

	p = s;
	while (num-- > 0)
		*p++ = (unsigned char) value;
	return (s);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char buffer1[20] = "Hello, world!";
	char buffer2[20] = "Hello, world!";
	
	printf("Before ft_memset: %s\n", buffer1);
	ft_memset(buffer1, '*', 5);
	printf("After ft_memset: %s\n", buffer1);
	
	printf("Before memset: %s\n", buffer2);
	memset(buffer2, '*', 5);
	printf("After memset: %s\n", buffer2);
	
	return (0);
}
*/