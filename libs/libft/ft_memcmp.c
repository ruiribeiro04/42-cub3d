/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:25:11 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/12 16:55:03 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*ps1;
	unsigned char	*ps2;

	ps1 = (unsigned char *)s1;
	ps2 = (unsigned char *)s2;
	if (!n)
		return (0);
	i = 0;
	while (ps1[i] == ps2[i] && i + 1 < n)
		i++;
	return (ps1[i] - ps2[i]);
}

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char s1[] = "Hello, world!";
	char s2[] = "Hello, there!";
	char s3[] = "Hello, world!";
	
	printf("String 1: \"%s\"\n", s1);
	printf("String 2: \"%s\"\n", s2);
	printf("String 3: \"%s\"\n\n", s3);
	
	// Compare s1 and s2 (different strings)
	printf("Comparing s1 and s2 (first 7 bytes):\n");
	printf("ft_memcmp: %d\n", ft_memcmp(s1, s2, 7));
	printf("memcmp: %d\n\n", memcmp(s1, s2, 7));
	
	printf("Comparing s1 and s2 (first 13 bytes):\n");
	printf("ft_memcmp: %d\n", ft_memcmp(s1, s2, 13));
	printf("memcmp: %d\n\n", memcmp(s1, s2, 13));
	
	// Compare s1 and s3 (identical strings)
	printf("Comparing s1 and s3 (first 13 bytes):\n");
	printf("ft_memcmp: %d\n", ft_memcmp(s1, s3, 13));
	printf("memcmp: %d\n", memcmp(s1, s3, 13));
	
	return (0);
}
*/
