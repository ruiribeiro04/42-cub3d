/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:58:21 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/14 16:14:28 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*p;
	size_t	i;

	i = 0;
	p = s;
	while (i < n)
	{
		p[i] = 0;
		i++;
	}
}

/*
#include <stdio.h>
#include <strings.h>

int	main(void)
{
	char buffer1[20] = "Hello, world!";
	char buffer2[20] = "Hello, world!";
	
	printf("Before ft_bzero: %s\n", buffer1);
	ft_bzero(buffer1, 5);
	printf("After ft_bzero (first 10 chars as hex): ");
	for (int i = 0; i < 10; i++)
		printf("%02x ", (unsigned char)buffer1[i]);
	printf("\n");
	
	printf("Before bzero: %s\n", buffer2);
	bzero(buffer2, 5);
	printf("After bzero (first 10 chars as hex): ");
	for (int i = 0; i < 10; i++)
		printf("%02x ", (unsigned char)buffer2[i]);
	printf("\n");
	
	return (0);
}
*/
