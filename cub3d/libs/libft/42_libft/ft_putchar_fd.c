/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:41:35 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/10 10:52:06 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/*
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int	main(void)
{
	int fd;
	
	// Write to standard output (fd 1)
	printf("Writing character 'A' to standard output (fd 1):\n");
	ft_putchar_fd('A', 1);
	ft_putchar_fd('\n', 1);
	
	// Write to a file
	printf("\nWriting character 'B' to test_putchar.txt:\n");
	fd = open("test_putchar.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		printf("Error opening file\n");
		return (1);
	}
	
	ft_putchar_fd('B', fd);
	close(fd);
	
	printf("Check test_putchar.txt for the result\n");
	
	return (0);
}
*/
