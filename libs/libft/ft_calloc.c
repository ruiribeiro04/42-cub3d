/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:02:24 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/14 21:33:24 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	memvalue;
	void	*p;

	memvalue = size * nmemb;
	p = malloc(memvalue);
	if (!p)
		return (NULL);
	ft_memset(p, 0, memvalue);
	return (p);
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	size_t count = 5;
	size_t size = sizeof(int);
	
	int *ft_array = (int *)ft_calloc(count, size);
	printf("ft_calloc result:\n");
	if (ft_array)
	{
		for (size_t i = 0; i < count; i++)
			printf("%d ", ft_array[i]);
		printf("\n\n");
	}
	else
		printf("ft_calloc failed\n\n");

	int *std_array = (int *)calloc(count, size);
	printf("calloc result:\n");
	if (std_array)
	{
		for (size_t i = 0; i < count; i++)
			printf("%d ", std_array[i]);
		printf("\n");
	}
	else
		printf("calloc failed\n");
	
	if (ft_array && std_array)
	{
		if (memcmp(ft_array, std_array, count * size) == 0)
			printf("Both arrays have the same content\n");
		else
			printf("Arrays differ\n");
	}
	
	free(ft_array);
	free(std_array);
	
	return (0);
}
*/
