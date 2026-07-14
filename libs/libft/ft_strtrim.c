/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:44:27 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/09 20:50:17 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[start]) && start <= end)
		start++;
	if (start > end)
		return (ft_strdup(s1 + end + 1));
	while (ft_strchr(set, s1[end]) && end >= 0)
		end--;
	str = malloc(end - start + 2);
	if (!str)
		return (NULL);
	ft_strlcpy(str, &s1[start], end - start + 2);
	return (str);
}

/*
#include <stdio.h>

int	main(void)
{
	char *str1 = "   Hello, world!   ";
	char *str2 = "...Hello, world!...";
	char *set1 = " ";
	char *set2 = ".";
	char *str3 = "abcHello, world!abc";
	char *set3 = "abc";
	
	// Test with spaces
	printf("Original: \"%s\", set: \"%s\"\n", str1, set1);
	char *result1 = ft_strtrim(str1, set1);
	printf("After ft_strtrim: \"%s\"\n\n", result1);
	
	// Test with dots
	printf("Original: \"%s\", set: \"%s\"\n", str2, set2);
	char *result2 = ft_strtrim(str2, set2);
	printf("After ft_strtrim: \"%s\"\n\n", result2);
	
	// Test with multiple characters in set
	printf("Original: \"%s\", set: \"%s\"\n", str3, set3);
	char *result3 = ft_strtrim(str3, set3);
	printf("After ft_strtrim: \"%s\"\n", result3);
	
	// Free allocated memory
	if (result1)
		free(result1);
	if (result2)
		free(result2);
	if (result3)
		free(result3);
	
	return (0);
}
*/
