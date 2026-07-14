/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:33:56 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/09 14:38:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		length;
	char	*d;

	i = 0;
	length = ft_strlen(s);
	d = malloc(length + 1);
	if (!d)
		return (NULL);
	while (s[i])
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char *original = "Test string";
	
	char *ft_copy = ft_strdup(original);
	char *std_copy = strdup(original);
	
	printf("Original: %s\n", original);
	printf("ft_strdup: %s\n", ft_copy);
	printf("strdup: %s\n", std_copy);
	
	if (ft_copy)
		free(ft_copy);
	if (std_copy)
		free(std_copy);
	
	return (0);
}
*/
