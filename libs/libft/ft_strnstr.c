/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:47:39 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/14 16:14:17 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] != '\0'
			&& big[i + j] == little[j] && i + j < len)
		{
			if (little[j + 1] == '\0')
				return ((char *)&big[i]);
			++j;
		}
		++i;
	}
	return (NULL);
}

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char haystack[] = "Hello, this is a simple test string";
	char needle1[] = "simple";
	char needle2[] = "not present";
	
	printf("Haystack: \"%s\"\n", haystack);
	printf("Needle 1: \"%s\"\n", needle1);
	
	// Limited search
	printf("\nSearch with len = 20 (needle1 outside this range):\n");
	printf("ft_strnstr: %s\n", ft_strnstr(haystack, needle1, 20));
	printf("strnstr: %s\n", strnstr(haystack, needle1, 20));
	
	// Full search
	printf("\nSearch with len = 36 (full string):\n");
	printf("ft_strnstr: %s\n", ft_strnstr(haystack, needle1, 36));
	printf("strnstr: %s\n", strnstr(haystack, needle1, 36));
	
	// Needle not found
	printf("\nNeedle 2: \"%s\"\n", needle2);
	printf("ft_strnstr: %s\n",ft_strnstr(haystack, needle2, 36)
		? ft_strnstr(haystack, needle2, 36) : "NULL");
	printf("strnstr: %s\n", strnstr(haystack, needle2, 36)
		? strnstr(haystack, needle2, 36) : "NULL");
	
	// Empty needle
	printf("\nEmpty needle:\n");
	printf("ft_strnstr: %s\n", ft_strnstr(haystack, "", 36));
	printf("strnstr: %s\n", strnstr(haystack, "", 36));
	
	return (0);
}
*/
