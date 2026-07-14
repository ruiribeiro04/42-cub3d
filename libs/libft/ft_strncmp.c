/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:03:33 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/13 20:57:41 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] != '\0' && s2[i] != '\0')
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
		{
			return (((unsigned char)s1[i])
				- ((unsigned char)s2[i]));
		}
		i++;
	}
	if (i < n)
	{
		return (((unsigned char)s1[i]) - ((unsigned char)s2[i]));
	}
	return (0);
}

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char *s1 = "Hello";
	char *s2 = "Hello, world";
	char *s3 = "Hellz";
	
	printf("Strings: \"%s\", \"%s\"\n", s1, s2);
	printf("ft_strncmp (n=5): %d\n", ft_strncmp(s1, s2, 5));
	printf("strncmp (n=5): %d\n\n", strncmp(s1, s2, 5));
	
	printf("Strings: \"%s\", \"%s\"\n", s1, s2);
	printf("ft_strncmp (n=8): %d\n", ft_strncmp(s1, s2, 8));
	printf("strncmp (n=8): %d\n\n", strncmp(s1, s2, 8));
	
	printf("Strings: \"%s\", \"%s\"\n", s1, s3);
	printf("ft_strncmp (n=5): %d\n", ft_strncmp(s1, s3, 5));
	printf("strncmp (n=5): %d\n", strncmp(s1, s3, 5));
	
	return (0);
}
*/
