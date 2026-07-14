/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:40:09 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/12 16:54:31 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}

/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	int test = 65;  // ASCII for 'A'
	
	printf("ft_isprint: %d\n", ft_isprint(test));
	printf("isprint: %d\n", isprint(test));
	
	test = 10;  // ASCII for newline (non-printable)
	printf("ft_isprint: %d\n", ft_isprint(test));
	printf("isprint: %d\n", isprint(test));
	
	return (0);
}
*/
