/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/11 16:00:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser_internal.h"
#include <fcntl.h>
#include <unistd.h>
#include <libft.h>

static int	ft_has_cub_extension(const char *path)
{
	size_t	len;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 5)
		return (0);
	return (ft_strncmp(path + len - 4, ".cub", 4) == 0);
}

static int	ft_parse_and_validate(int fd, t_config *cfg)
{
	if (ft_parse_lines(fd, cfg) < 0)
	{
		ft_drain_fd(fd);
		return (-1);
	}
	return (ft_validate_config(cfg));
}

t_config	*ft_parse_cub_file(const char *path)
{
	int			fd;
	t_config	*cfg;

	if (!ft_has_cub_extension(path))
		return (ft_cub_error_ret("File must end with .cub", NULL));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_cub_error_ret("Cannot open scene file", NULL));
	cfg = ft_alloc_config();
	if (!cfg)
	{
		close(fd);
		return (ft_cub_error_ret("Memory allocation failed", NULL));
	}
	if (ft_parse_and_validate(fd, cfg) < 0)
	{
		close(fd);
		ft_free_config(cfg);
		return (NULL);
	}
	close(fd);
	return (cfg);
}
