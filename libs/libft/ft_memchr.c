/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:12:02 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/12 16:54:48 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
			return (&str[i]);
		i++;
	}
	return (0);
}

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char str[] = "Hello, world!";
	int c = 'w';
	size_t n = strlen(str);
	
	printf("String: \"%s\", looking for: '%c'\n", str, c);
	
	void *ft_result = ft_memchr(str, c, n);
	void *std_result = memchr(str, c, n);
	
	printf("ft_memchr result: %p, \"%s\"\n", 
		ft_result, ft_result ? (char *)ft_result : "NULL");
	printf("memchr result: %p, \"%s\"\n\n", std_result,
		std_result ? (char *)std_result : "NULL");
	
	// Test character not found
	c = 'z';
	printf("String: \"%s\", looking for: '%c'\n", str, c);
	
	ft_result = ft_memchr(str, c, n);
	std_result = memchr(str, c, n);
	
	printf("ft_memchr result: %p, %s\n", ft_result,
		ft_result ? (char *)ft_result : "NULL");
	printf("memchr result: %p, %s\n", std_result,
		std_result ? (char *)std_result : "NULL");
	
	return (0);
}
*/
