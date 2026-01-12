/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-maga <vde-maga@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:09:03 by vde-maga          #+#    #+#             */
/*   Updated: 2025/04/14 14:18:27 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
//#include <fcntl.h>
//#include <unistd.h>
//#include <stdio.h>

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s || fd < 0)
		return ;
	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}
/*
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

int	main(void)
{
	int	fd;

	ft_putstr_fd("Teste: Hello, world!\n", 1);
	ft_putstr_fd("", 1);
	ft_putstr_fd("\n", 1);
	fd = open("teste.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("Erro ao abrir o arquivo");
		return (1);
	}
	ft_putstr_fd("Este é um teste para escrever no arquivo teste.txt\n", fd);
	close(fd);
	ft_putstr_fd(NULL, 1);
	ft_putstr_fd("Teste com fd inválido\n", -1);
	return (0);
}
*/
