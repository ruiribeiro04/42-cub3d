/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:23:54 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/09 19:51:50 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;
	size_t	sum_join;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	sum_join = dst_len + src_len;
	if (size <= dst_len)
		return (src_len + size);
	i = 0;
	while (src[i] && (dst_len + 1) < size)
		dst[dst_len++] = src[i++];
	dst[dst_len] = '\0';
	return (sum_join);
}

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char dest1[30] = "First part";
	char dest2[30] = "First part";
	char *src = " - Second part";
	size_t result1, result2;
	
	printf("Original dest: \"%s\", src: \"%s\"\n", dest1, src);
	
	// Test normal concatenation
	result1 = ft_strlcat(dest1, src, sizeof(dest1));
	result2 = strlcat(dest2, src, sizeof(dest2));
	
	printf("ft_strlcat: result=%zu, dest=\"%s\"\n", result1, dest1);
	printf("strlcat: result=%zu, dest=\"%s\"\n", result2, dest2);
	
	// Test with limited size
	char dest3[15] = "First part";
	char dest4[15] = "First part";
	
	result1 = ft_strlcat(dest3, src, sizeof(dest3));
	result2 = strlcat(dest4, src, sizeof(dest4));
	
	printf("\nLimited size test:\n");
	printf("ft_strlcat: result=%zu, dest=\"%s\"\n", result1, dest3);
	printf("strlcat: result=%zu, dest=\"%s\"\n", result2, dest4);
	
	return (0);
}
*/
