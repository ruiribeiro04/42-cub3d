/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:51:48 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/11 16:58:57 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t num)
{
	unsigned char	*pdest;
	unsigned char	*psrc;
	size_t			i;

	if (!dest && !src)
		return (0);
	pdest = (unsigned char *)dest;
	psrc = (unsigned char *)src;
	i = 0;
	while (i < num)
	{
		pdest[i] = psrc[i];
		i++;
	}
	return (dest);
}

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char src[] = "Source string";
	char dest1[20] = {0};
	char dest2[20] = {0};
	
	ft_memcpy(dest1, src, strlen(src));
	printf("ft_memcpy result: %s\n", dest1);
	
	memcpy(dest2, src, strlen(src));
	printf("memcpy result: %s\n", dest2);
	
	return (0);
}
*/
