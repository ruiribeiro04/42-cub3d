/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:43:25 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/05 15:10:50 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char *test = "Hello, world!";
	
	printf("ft_strlen: %zu\n", ft_strlen(test));
	printf("strlen: %zu\n", strlen(test));
	
	test = "";
	printf("ft_strlen: %zu\n", ft_strlen(test));
	printf("strlen: %zu\n", strlen(test));
	
	return (0);
}
*/
