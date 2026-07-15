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

static int	has_cub_extension(const char *path)
{
	size_t	len;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 5)
		return (0);
	return (ft_strncmp(path + len - 4, ".cub", 4) == 0);
}

static int	parse_and_validate(int fd, t_config *cfg)
{
	if (parse_lines(fd, cfg) < 0)
	{
		drain_fd(fd);
		return (-1);
	}
	return (validate_config(cfg));
}

t_config	*parse_cub_file(const char *path)
{
	int			fd;
	t_config	*cfg;

	if (!has_cub_extension(path))
		return (cub_error_ret("File must end with .cub", NULL));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (cub_error_ret("Cannot open scene file", NULL));
	cfg = alloc_config();
	if (!cfg)
	{
		close(fd);
		return (cub_error_ret("Memory allocation failed", NULL));
	}
	if (parse_and_validate(fd, cfg) < 0)
	{
		close(fd);
		free_config(cfg);
		return (NULL);
	}
	close(fd);
	return (cfg);
}
