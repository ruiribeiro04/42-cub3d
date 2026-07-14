/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 21:20:09 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/14 16:22:07 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_num_len(int n)
{
	int	len;

	len = 1;
	if (n < 0)
		len++;
	while (n / 10 != 0 && ++len)
		n /= 10;
	return (len);
}

static void	ft_fill(char *p, long n, int len)
{
	while (n > 0)
	{
		p[--len] = n % 10 + '0';
		n /= 10;
	}
}

char	*ft_itoa(int num)
{
	long	n;
	int		len;
	char	*p;

	n = num;
	len = ft_num_len(n);
	p = (char *)malloc(len + 1);
	if (!p)
		return (NULL);
	p[len] = '\0';
	if (n == 0)
		p[0] = '0';
	else if (n < 0)
	{
		p[0] = '-';
		n = -n;
	}
	if (n == -2147483648L)
	{
		ft_strlcpy(p, "-2147483648", 12);
		return (p);
	}
	ft_fill(p, n, len);
	return (p);
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int	main(void)
{
	int test_numbers[] = {0, 42, -42, 2147483647, -2147483648, 123456, -123456};
	int num_tests = sizeof(test_numbers) / sizeof(test_numbers[0]);
	
	for (int i = 0; i < num_tests; i++)
	{
		char *result = ft_itoa(test_numbers[i]);
		printf("Number: %d\n", test_numbers[i]);
		printf("ft_itoa result: \"%s\"\n\n", result);
		
		if (result)
			free(result);
	}
	
	return (0);
}
*/
