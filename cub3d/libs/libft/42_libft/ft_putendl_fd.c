/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:11:03 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/10 12:22:10 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
	ft_putchar_fd('\n', fd);
}

/*
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int	main(void)
{
	int fd;
	
	// Write to standard output (fd 1)
	printf("Writing string with newline to standard output (fd 1):\n");
	ft_putendl_fd("First line", 1);
	ft_putendl_fd("Second line", 1);
	
	// Write to a file
	printf("\nWriting string with newline to test_putendl.txt:\n");
	fd = open("test_putendl.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		printf("Error opening file\n");
		return (1);
	}
	
	ft_putendl_fd("First line in file", fd);
	ft_putendl_fd("Second line in file", fd);
	close(fd);
	
	printf("Check test_putendl.txt for the result\n");
	
	return (0);
}
*/
