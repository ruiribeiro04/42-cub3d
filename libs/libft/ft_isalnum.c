/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:13:03 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/14 16:21:44 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	char test = 'A';
	
	printf("ft_isalnum: %d\n", ft_isalnum(test));
	printf("isalnum: %d\n", isalnum(test));
	
	test = '5';
	printf("ft_isalnum: %d\n", ft_isalnum(test));
	printf("isalnum: %d\n", isalnum(test));
	
	test = '@';
	printf("ft_isalnum: %d\n", ft_isalnum(test));
	printf("isalnum: %d\n", isalnum(test));
	
	return (0);
}
*/
