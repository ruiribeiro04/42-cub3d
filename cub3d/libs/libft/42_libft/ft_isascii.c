/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:32:01 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/14 16:21:59 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}

/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	int test = 65;  // ASCII for 'A'
	
	printf("ft_isascii: %d\n", ft_isascii(test));
	printf("isascii: %d\n", isascii(test));
	
	test = 128;  // Outside ASCII range
	printf("ft_isascii: %d\n", ft_isascii(test));
	printf("isascii: %d\n", isascii(test));
	
	return (0);
}
*/
