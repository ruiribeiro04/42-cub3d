/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:10:17 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/14 16:22:02 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	char test = '5';
	
	printf("ft_isdigit: %d\n", ft_isdigit(test));
	printf("isdigit: %d\n", isdigit(test));
	
	test = 'A';
	printf("ft_isdigit: %d\n", ft_isdigit(test));
	printf("isdigit: %d\n", isdigit(test));
	
	return (0);
}
*/
