/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:55:27 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/10 12:29:09 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_abs(int n)
{
	if (n < 0)
		return (n * (-1));
	else
		return (n);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	num;

	if (n < 0)
		ft_putchar_fd('-', fd);
	num = ft_abs(n);
	if (num >= 10)
	{
		ft_putnbr_fd(num / 10, fd);
		ft_putnbr_fd(num % 10, fd);
	}
	else
		ft_putchar_fd(num + '0', fd);
}

/*
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

int	main(void)
{
	int fd;
	
	// Test cases for standard output (fd 1)
	printf("Testing ft_putnbr_fd to standard output (fd 1):\n");
	
	printf("Number 42: ");
	ft_putnbr_fd(42, 1);
	printf("\n");
	
	printf("Number -42: ");
	ft_putnbr_fd(-42, 1);
	printf("\n");
	
	printf("Number 0: ");
	ft_putnbr_fd(0, 1);
	printf("\n");
	
	printf("INT_MAX (%d): ", INT_MAX);
	ft_putnbr_fd(INT_MAX, 1);
	printf("\n");
	
	printf("INT_MIN (%d): ", INT_MIN);
	ft_putnbr_fd(INT_MIN, 1);
	printf("\n");
	
	// Test with file output
	printf("\nWriting numbers to test_putnbr.txt\n");
	fd = open("test_putnbr.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		printf("Error opening file\n");
		return (1);
	}
	
	ft_putnbr_fd(12345, fd);
	ft_putchar_fd('\n', fd);
	ft_putnbr_fd(-9876, fd);
	ft_putchar_fd('\n', fd);
	close(fd);
	
	printf("Check test_putnbr.txt for the result\n");
	
	return (0);
}
*/
