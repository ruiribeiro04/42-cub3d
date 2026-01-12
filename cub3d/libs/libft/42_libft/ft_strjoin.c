/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:33:30 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/09 20:32:46 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	sum;
	char			*join;
	int				i;
	int				j;

	if (!s1 || !s2)
		return (0);
	sum = ft_strlen(s1) + ft_strlen(s2);
	join = (char *) malloc ((sizeof(char) * sum) + 1);
	if (!join)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		++i;
	}
	j = 0;
	while (s2[j])
	{
		join[i + j] = s2[j];
		++j;
	}
	join[i + j] = '\0';
	return (join);
}

/*
#include <stdio.h>

int	main(void)
{
	char *s1 = "Hello, ";
	char *s2 = "world!";
	char *s3 = "";
	
	printf("String 1: \"%s\"\n", s1);
	printf("String 2: \"%s\"\n", s2);
	
	// Test normal join
	char *result1 = ft_strjoin(s1, s2);
	printf("Result of ft_strjoin: \"%s\"\n\n", result1);
	
	// Test with empty string
	printf("String 3: \"%s\" (empty string)\n", s3);
	char *result2 = ft_strjoin(s1, s3);
	char *result3 = ft_strjoin(s3, s2);
	char *result4 = ft_strjoin(s3, s3);
	
	printf("ft_strjoin(s1, s3): \"%s\"\n", result2);
	printf("ft_strjoin(s3, s2): \"%s\"\n", result3);
	printf("ft_strjoin(s3, s3): \"%s\"\n", result4);
	
	// Free allocated memory
	if (result1)
		free(result1);
	if (result2)
		free(result2);
	if (result3)
		free(result3);
	if (result4)
		free(result4);
	
	return (0);
}
*/
