/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-maga <vde-maga@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:14:32 by vde-maga          #+#    #+#             */
/*   Updated: 2025/04/15 13:47:22 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
//#include <fcntl.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
/*
int	main(void)
{
	int		fd;
	char	c;

	// Testando saída para o console (file descriptor padrão: 1)
	c = 'A';
	ft_putchar_fd(c, 1);
	ft_putchar_fd('\n', 1);
	// Testando saída para um arquivo
	fd = open("putchar_test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		write(2, "Erro ao abrir o arquivo.\n", 26);
		return (1);
	}
	ft_putchar_fd('B', fd);
	ft_putchar_fd('\n', fd);
	close(fd);
	return (0);
}
*/
