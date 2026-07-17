/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/11 16:00:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"
#include <unistd.h>
#include <libft.h>

static void	putstr_endl(const char *s, int fd)
{
	size_t	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	write(fd, s, len);
	write(fd, "\n", 1);
}

void	ft_cub_error(const char *msg)
{
	putstr_endl("Error", STDERR_FILENO);
	if (msg)
		putstr_endl(msg, STDERR_FILENO);
}

void	*ft_cub_error_ret(const char *msg, void *ret)
{
	ft_cub_error(msg);
	return (ret);
}

int	ft_cub_error_int(const char *msg)
{
	ft_cub_error(msg);
	return (-1);
}
