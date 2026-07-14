/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:15:34 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/10 10:39:23 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned long	i;
	unsigned long	len;
	char			*str;

	len = ft_strlen(s);
	str = (char *) malloc (sizeof (char) * (len + 1));
	if (!str)
		return (NULL);
	if (str == 0)
		return (str);
	i = 0;
	while (i < len)
	{
		str[i] = (*f)(i, s[i]);
		++i;
	}
	str[i] = 0;
	return (str);
}

/*
#include <stdio.h>

// Função de teste
char	example_func(unsigned int i, char c)
{
	if (i % 2 == 0)
		return (c >= 'a' && c <= 'z') ? c - 32 : c;
	return c;
}

int	main(void)
{
	char *str = "hello, world!";
	
	printf("Original string: \"%s\"\n", str);
	
	char *result = ft_strmapi(str, &example_func);
	printf("After ft_strmapi: \"%s\"\n", result);
	
	if (result)
		free(result);
	
	return (0);
}
*/
