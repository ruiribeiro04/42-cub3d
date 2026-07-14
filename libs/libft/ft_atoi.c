/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:01:04 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/13 20:57:14 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	i;
	int	signal;
	int	result;

	i = 0;
	signal = 1;
	result = 0;
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signal *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (signal * result);
}
/*
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char *test_strings[] = {
		"42",
		"-42",
		"  +42",
		"  -42abc",
		"2147483647",
		"-2147483648",
		"0"
	};
	
	for (int i = 0; i < 7; i++)
	{
		printf("String: '%s'\n", test_strings[i]);
		printf("ft_atoi: %d\n", ft_atoi(test_strings[i]));
		printf("atoi: %d\n\n", atoi(test_strings[i]));
	}
	
	return (0);
}
*/
