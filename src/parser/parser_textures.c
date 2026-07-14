/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_textures.c                                  :+:      :+:    :+:   */
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

static char	*extract_token(const char **p)
{
	const char	*start;
	char		*token;
	size_t		len;

	start = *p;
	while (**p != '\0' && **p != ' ' && **p != '\t')
		(*p)++;
	len = (size_t)(*p - start);
	token = (char *)malloc(len + 1);
	if (!token)
	{
		cub_error("Memory allocation failed");
		return (NULL);
	}
	ft_strlcpy(token, start, len + 1);
	return (token);
}

static int	verify_path_readable(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	close(fd);
	return (0);
}

static int	set_texture_field(const char *line, t_config *cfg,
								char *path)
{
	if (verify_path_readable(path) < 0)
	{
		cub_error("Texture file cannot be opened");
		free(path);
		return (-1);
	}
	if (ft_strncmp(line, "NO", 2) == 0 && !cfg->has_north)
		return (cfg->textures.north = path, cfg->has_north = 1, 0);
	if (ft_strncmp(line, "SO", 2) == 0 && !cfg->has_south)
		return (cfg->textures.south = path, cfg->has_south = 1, 0);
	if (ft_strncmp(line, "WE", 2) == 0 && !cfg->has_west)
		return (cfg->textures.west = path, cfg->has_west = 1, 0);
	if (ft_strncmp(line, "EA", 2) == 0 && !cfg->has_east)
		return (cfg->textures.east = path, cfg->has_east = 1, 0);
	cub_error("Duplicate texture identifier");
	free(path);
	return (-1);
}

int	parse_texture_line(const char *line, t_config *cfg)
{
	const char	*p;
	char		*path;

	if (line[2] != ' ' && line[2] != '\t')
		return (cub_error_int("Texture id must be followed by ws"));
	p = line + 2;
	skip_spaces(&p);
	if (*p == '\0')
		return (cub_error_int("Missing texture path"));
	path = extract_token(&p);
	if (!path)
		return (-1);
	skip_spaces(&p);
	if (*p != '\0')
	{
		cub_error("Unexpected text after texture path");
		free(path);
		return (-1);
	}
	return (set_texture_field(line, cfg, path));
}
