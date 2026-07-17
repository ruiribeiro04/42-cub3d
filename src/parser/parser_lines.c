/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lines.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/15 16:00:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser_internal.h"
#include <stdlib.h>
#include <libft.h>


int	ft_parse_element_line(const char *line, t_config *cfg)
{
	if ((ft_strncmp(line, "NO ", 3) == 0
			|| ft_strncmp(line, "NO\t", 3) == 0)
		|| (ft_strncmp(line, "SO ", 3) == 0
			|| ft_strncmp(line, "SO\t", 3) == 0)
		|| (ft_strncmp(line, "WE ", 3) == 0
			|| ft_strncmp(line, "WE\t", 3) == 0)
		|| (ft_strncmp(line, "EA ", 3) == 0
			|| ft_strncmp(line, "EA\t", 3) == 0))
		return (ft_parse_texture_line(line, cfg));
	if (ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "F\t", 2) == 0)
		return (ft_parse_color_line(line, cfg));
	if (ft_strncmp(line, "C ", 2) == 0
		|| ft_strncmp(line, "C\t", 2) == 0)
		return (ft_parse_color_line(line, cfg));
	if ((ft_strncmp(line, "SP ", 3) == 0
			|| ft_strncmp(line, "SP\t", 3) == 0))
		return (ft_parse_sprite_line(line, cfg));
	if ((ft_strncmp(line, "DO ", 3) == 0
			|| ft_strncmp(line, "DO\t", 3) == 0))
		return (ft_parse_door_line(line, cfg));
	ft_cub_error("Unknown element identifier");
	return (-1);
}


static int	ft_handle_line(char **line, t_config *cfg)
{
	char	*expanded;

	expanded = ft_expand_tabs(*line);
	if (!expanded)
	{
		ft_cub_error("Memory allocation failed");
		free(*line);
		return (-1);
	}
	free(*line);
	*line = expanded;
	if (ft_is_blank_line(*line))
		return (1);
	if (ft_looks_like_map(*line))
		return (2);
	if (ft_parse_element_line(*line, cfg) < 0)
		return (-1);
	return (0);
}

int	ft_parse_lines(int fd, t_config *cfg)
{
	char	*line;
	int		status;

	line = get_next_line(fd);
	while (line != NULL)
	{
		ft_strip_newline(line);
		status = ft_handle_line(&line, cfg);
		if (status == -1)
		{
			free(line);
			return (-1);
		}
		if (status == 2)
			return (ft_parse_map_block(fd, line, cfg));
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}
