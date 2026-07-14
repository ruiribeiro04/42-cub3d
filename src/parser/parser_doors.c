/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_doors.c                                     :+:      :+:    :+:   */
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
#include <stdlib.h>
#include <libft.h>

static int	verify_door_path(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	close(fd);
	return (0);
}

static char	*extract_door_path(const char *line)
{
	const char	*p;
	char		*path;
	size_t		len;

	p = line + 2;
	skip_spaces(&p);
	if (*p == '\0')
	{
		cub_error("Missing door texture path");
		return (NULL);
	}
	len = ft_strlen(p);
	while (len > 0 && (p[len - 1] == ' ' || p[len - 1] == '\t'))
		len--;
	path = (char *)malloc(len + 1);
	if (!path)
	{
		cub_error("Memory allocation failed");
		return (NULL);
	}
	ft_strlcpy(path, p, len + 1);
	return (path);
}

int	parse_door_line(const char *line, t_config *cfg)
{
	char	*path;

	if (cfg->has_door_texture)
		return (cub_error_int("Duplicate DO identifier"));
	if (line[2] != ' ' && line[2] != '\t')
		return (cub_error_int("DO id must be followed by ws"));
	path = extract_door_path(line);
	if (!path)
		return (-1);
	if (verify_door_path(path) < 0)
	{
		cub_error("Door texture file cannot be opened");
		free(path);
		return (-1);
	}
	cfg->door_texture = path;
	cfg->has_door_texture = 1;
	return (0);
}
