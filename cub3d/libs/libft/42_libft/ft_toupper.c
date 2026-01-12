/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 12:13:15 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/14 21:29:27 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}

/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	int c;
	
	// Test lowercase letter
	c = 'a';
	printf("Original: '%c' (%d)\n", c, c);
	printf("ft_toupper: '%c' (%d)\n", ft_toupper(c), ft_toupper(c));
	printf("toupper: '%c' (%d)\n\n", toupper(c), toupper(c));
	
	// Test uppercase letter
	c = 'Z';
	printf("Original: '%c' (%d)\n", c, c);
	printf("ft_toupper: '%c' (%d)\n", ft_toupper(c), ft_toupper(c));
	printf("toupper: '%c' (%d)\n\n", toupper(c), toupper(c));
	
	// Test non-letter
	c = '5';
	printf("Original: '%c' (%d)\n", c, c);
	printf("ft_toupper: '%c' (%d)\n", ft_toupper(c), ft_toupper(c));
	printf("toupper: '%c' (%d)\n", toupper(c), toupper(c));
	
	return (0);
}
*/
