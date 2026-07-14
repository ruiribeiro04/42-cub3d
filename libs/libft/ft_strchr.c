/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:15:11 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/09 20:37:52 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (char)c)
	{
		if (s[i] == '\0')
			return (NULL);
		i++;
	}
	return ((char *)&s[i]);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char str[] = "Hello, world!";
	char ch = 'o';
	
	printf("String: %s\n", str);
	printf("Character to find: %c\n", ch);
	
	char *ft_result = ft_strchr(str, ch);
	char *std_result = strchr(str, ch);
	
	printf("ft_strchr result: %s\n", ft_result);
	printf("strchr result: %s\n", std_result);
	
	return (0);
}
*/
