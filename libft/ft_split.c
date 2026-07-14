/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:17:36 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/14 17:39:42 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_count_words(char const *s, char c)
{
	size_t	count;
	int		is_word;

	count = 0;
	is_word = 0;
	while (*s)
	{
		if (*s != c && is_word == 0)
		{
			is_word = 1;
			count++;
		}
		else if (*s == c)
			is_word = 0;
		s++;
	}
	return (count);
}

static char	*ft_extract_word(char const **s_ptr, char c)
{
	char const	*word_start;
	size_t		len;
	char		*word;

	while (**s_ptr && **s_ptr == c)
		(*s_ptr)++;
	word_start = *s_ptr;
	len = 0;
	while (**s_ptr && **s_ptr != c)
	{
		len++;
		(*s_ptr)++;
	}
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, word_start, len + 1);
	return (word);
}

static void	ft_free_memory(char **result, size_t words_allocated)
{
	while (words_allocated > 0)
	{
		words_allocated--;
		free(result[words_allocated]);
	}
	free(result);
}

char	**ft_split(char const *s, char c)
{
	char		**result;
	size_t		word_count;
	size_t		i;
	char const	*s_cursor;

	if (!s)
		return (NULL);
	word_count = ft_count_words(s, c);
	result = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	i = 0;
	s_cursor = s;
	while (i < word_count)
	{
		result[i] = ft_extract_word(&s_cursor, c);
		if (!result[i])
		{
			ft_free_memory(result, i);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}

/*
#include <stdio.h>

int	main(void)
{
	char *str1 = "Hello,world,this,is,a,test";
	char c1 = ',';
	
	char *str2 = "  Multiple   spaces   here  ";
	char c2 = ' ';
	
	char *str3 = "NoDelimiterHere";
	char c3 = ',';
	
	// Test with commas
	printf("Original: \"%s\", delimiter: '%c'\n", str1, c1);
	char **result1 = ft_split(str1, c1);
	if (result1)
	{
		printf("After ft_split:\n");
		for (int i = 0; result1[i]; i++)
			printf("[%d]: \"%s\"\n", i, result1[i]);
		printf("\n");
	}
	
	// Test with spaces
	printf("Original: \"%s\", delimiter: '%c'\n", str2, c2);
	char **result2 = ft_split(str2, c2);
	if (result2)
	{
		printf("After ft_split:\n");
		for (int i = 0; result2[i]; i++)
			printf("[%d]: \"%s\"\n", i, result2[i]);
		printf("\n");
	}
	
	// Test with no delimiter
	printf("Original: \"%s\", delimiter: '%c'\n", str3, c3);
	char **result3 = ft_split(str3, c3);
	if (result3)
	{
		printf("After ft_split:\n");
		for (int i = 0; result3[i]; i++)
			printf("[%d]: \"%s\"\n", i, result3[i]);
	}
	
	// Free allocated memory
	if (result1)
	{
		for (int i = 0; result1[i]; i++)
			free(result1[i]);
		free(result1);
	}
	
	if (result2)
	{
		for (int i = 0; result2[i]; i++)
			free(result2[i]);
		free(result2);
	}
	
	if (result3)
	{
		for (int i = 0; result3[i]; i++)
			free(result3[i]);
		free(result3);
	}
	
	return (0);
}
*/
