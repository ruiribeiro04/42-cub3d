/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:01:39 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/14 16:21:49 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	char test = 'A';
	
	printf("ft_isalpha: %d\n", ft_isalpha(test));
	printf("isalpha: %d\n", isalpha(test));
	
	test = '5';
	printf("ft_isalpha: %d\n", ft_isalpha(test));
	printf("isalpha: %d\n", isalpha(test));
	
	return (0);
}
*/
