/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 10:00:55 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/06 15:52:16 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*pdest;
	unsigned char	*psrc;

	pdest = (unsigned char *)dest;
	psrc = (unsigned char *)src;
	if (pdest == psrc || n == 0)
		return (dest);
	if (pdest < psrc)
		while (n-- > 0)
			*pdest++ = *psrc++;
	else
	{
		pdest += n - 1;
		psrc += n - 1;
		while (n-- > 0)
			*pdest-- = *psrc--;
	}
	return (dest);
}

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char str1[] = "memmove can be useful......";
	char str2[] = "memmove can be useful......";
	
	printf("Before ft_memmove: %s\n", str1);
	ft_memmove(str1 + 10, str1, 10);
	printf("After ft_memmove: %s\n", str1);
	
	printf("Before memmove: %s\n", str2);
	memmove(str2 + 10, str2, 10);
	printf("After memmove: %s\n", str2);
	
	return (0);
}
*/
