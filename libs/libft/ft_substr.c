/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:33:09 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/09 21:07:46 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		len = 0;
	else
	{
		if (len > s_len - start)
			len = s_len - start;
	}
	p = (char *)malloc(len + 1);
	if (!p)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		p[i] = s[start + i];
		i++;
	}
	p[i] = 0;
	return (p);
}

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char *str = "Hello, world!";
	
	// Test normal case
	char *sub1 = ft_substr(str, 7, 5);
	printf("Original: %s\n", str);
	printf("Substring (7, 5): %s\n", sub1);
	
	// Test start beyond string length
	char *sub2 = ft_substr(str, 20, 5);
	printf("Substring (20, 5): %s\n", sub2);
	
	// Test length beyond string end
	char *sub3 = ft_substr(str, 7, 20);
	printf("Substring (7, 20): %s\n", sub3);
	
	if (sub1)
		free(sub1);
	if (sub2)
		free(sub2);
	if (sub3)
		free(sub3);
	
	return (0);
}
*/
