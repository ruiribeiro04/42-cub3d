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

static int	parse_element_line(const char *line, t_config *cfg)
{
	if ((ft_strncmp(line, "NO ", 3) == 0
			|| ft_strncmp(line, "NO\t", 3) == 0)
		|| (ft_strncmp(line, "SO ", 3) == 0
			|| ft_strncmp(line, "SO\t", 3) == 0)
		|| (ft_strncmp(line, "WE ", 3) == 0
			|| ft_strncmp(line, "WE\t", 3) == 0)
		|| (ft_strncmp(line, "EA ", 3) == 0
			|| ft_strncmp(line, "EA\t", 3) == 0))
		return (parse_texture_line(line, cfg));
	if (ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "F\t", 2) == 0)
		return (parse_color_line(line, cfg));
	if (ft_strncmp(line, "C ", 2) == 0
		|| ft_strncmp(line, "C\t", 2) == 0)
		return (parse_color_line(line, cfg));
	if ((ft_strncmp(line, "SP ", 3) == 0
			|| ft_strncmp(line, "SP\t", 3) == 0))
		return (parse_sprite_line(line, cfg));
	if ((ft_strncmp(line, "DO ", 3) == 0
			|| ft_strncmp(line, "DO\t", 3) == 0))
		return (parse_door_line(line, cfg));
	cub_error("Unknown element identifier");
	return (-1);
}

static int	parse_lines(int fd, t_config *cfg)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		strip_newline(line);
		if (is_blank_line(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (looks_like_map(line))
			return (parse_map_block(fd, line, cfg));
		if (parse_element_line(line, cfg) < 0)
		{
			free(line);
			return (-1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
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
