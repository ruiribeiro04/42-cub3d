/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 12:13:15 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/13 20:57:47 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}

/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	int c;
	
	// Test uppercase letter
	c = 'A';
	printf("Original: '%c' (%d)\n", c, c);
	printf("ft_tolower: '%c' (%d)\n", ft_tolower(c), ft_tolower(c));
	printf("tolower: '%c' (%d)\n\n", tolower(c), tolower(c));
	
	// Test lowercase letter
	c = 'z';
	printf("Original: '%c' (%d)\n", c, c);
	printf("ft_tolower: '%c' (%d)\n", ft_tolower(c), ft_tolower(c));
	printf("tolower: '%c' (%d)\n\n", tolower(c), tolower(c));
	
	// Test non-letter
	c = '5';
	printf("Original: '%c' (%d)\n", c, c);
	printf("ft_tolower: '%c' (%d)\n", ft_tolower(c), ft_tolower(c));
	printf("tolower: '%c' (%d)\n", tolower(c), tolower(c));
	
	return (0);
}
*/
