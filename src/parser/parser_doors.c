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

int	parse_door_line(const char *line, t_config *cfg)
{
	char	*path;

	if (cfg->has_door_texture)
		return (cub_error_int("Duplicate DO identifier"));
	if (line[2] != ' ' && line[2] != '\t')
		return (cub_error_int("DO id must be followed by ws"));
	path = extract_path(line);
	if (!path)
		return (-1);
	if (!path_readable(path))
	{
		cub_error("Door texture file cannot be opened");
		free(path);
		return (-1);
	}
	cfg->door_texture = path;
	cfg->has_door_texture = 1;
	return (0);
}
