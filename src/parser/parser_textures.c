/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 12:21:47 by ruiferna          #+#    #+#             */
/*   Updated: 2026/07/17 17:26:24 by ruiferna         ###   ########.fr       */
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
		ft_cub_error("Memory allocation failed");
		return (NULL);
	}
	ft_strlcpy(token, start, len + 1);
	return (token);
}

char	*ft_extract_path(const char *line)
{
	const char	*p;
	char		*path;
	size_t		len;

	p = line + 2;
	ft_skip_spaces(&p);
	if (*p == '\0')
	{
		ft_cub_error("Missing texture path");
		return (NULL);
	}
	len = ft_strlen(p);
	while (len > 0 && (p[len - 1] == ' ' || p[len - 1] == '\t'))
		len--;
	path = (char *)malloc(len + 1);
	if (!path)
	{
		ft_cub_error("Memory allocation failed");
		return (NULL);
	}
	ft_strlcpy(path, p, len + 1);
	return (path);
}

static int	set_texture_field(const char *line, t_config *cfg,
							char *path)
{
	if (!ft_path_readable(path))
	{
		ft_cub_error("Texture file cannot be opened");
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
	ft_cub_error("Duplicate texture identifier");
	free(path);
	return (-1);
}

int	ft_parse_texture_line(const char *line, t_config *cfg)
{
	const char	*p;
	char		*path;

	if (line[2] != ' ' && line[2] != '\t')
		return (ft_cub_error_int("Texture id must be followed by ws"));
	p = line + 2;
	ft_skip_spaces(&p);
	if (*p == '\0')
		return (ft_cub_error_int("Missing texture path"));
	path = extract_token(&p);
	if (!path)
		return (-1);
	ft_skip_spaces(&p);
	if (*p != '\0')
	{
		ft_cub_error("Unexpected text after texture path");
		free(path);
		return (-1);
	}
	return (set_texture_field(line, cfg, path));
}
