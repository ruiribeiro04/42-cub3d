/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:45:10 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/10 10:50:31 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

/*
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int	main(void)
{
	int fd;
	
	// Write to standard output (fd 1)
	printf("Writing string to standard output (fd 1):\n");
	ft_putstr_fd("Hello, world!\n", 1);
	
	// Write to a file
	printf("\nWriting string to test_putstr.txt:\n");
	fd = open("test_putstr.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		printf("Error opening file\n");
		return (1);
	}
	
	ft_putstr_fd("Test string in file", fd);
	close(fd);
	
	printf("Check test_putstr.txt for the result\n");
	
	return (0);
}
*/
