/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:42:53 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/13 21:49:04 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (i < size - 1 && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char dest1[20];
	char dest2[20];
	char *src = "Hello, world!";
	size_t result1, result2;
	
	// Test normal case
	result1 = ft_strlcpy(dest1, src, sizeof(dest1));
	result2 = strlcpy(dest2, src, sizeof(dest2));
	
	printf("Source: %s\n", src);
	printf("ft_strlcpy: result=%zu, dest=\"%s\"\n", result1, dest1);
	printf("strlcpy: result=%zu, dest=\"%s\"\n", result2, dest2);
	
	// Test with size smaller than source
	result1 = ft_strlcpy(dest1, src, 5);
	result2 = strlcpy(dest2, src, 5);
	
	printf("\nCopy with limited size (5):\n");
	printf("ft_strlcpy: result=%zu, dest=\"%s\"\n", result1, dest1);
	printf("strlcpy: result=%zu, dest=\"%s\"\n", result2, dest2);
	
	return (0);
}
*/
