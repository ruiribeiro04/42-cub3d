/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 12:21:47 by ruiferna          #+#    #+#             */
/*   Updated: 2026/07/17 17:26:37 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <libft.h>

int	ft_parse_sprite_line(const char *line, t_config *cfg)
{
	char	*path;

	if (cfg->has_sprite)
		return (ft_cub_error_int("Duplicate SP identifier"));
	if (line[2] != ' ' && line[2] != '\t')
		return (ft_cub_error_int("SP id must be followed by ws"));
	path = ft_extract_path(line);
	if (!path)
		return (-1);
	if (ft_strlen(path) > SPRITE_PATH_MAX)
	{
		ft_cub_error("Sprite texture path too long");
		free(path);
		return (-1);
	}
	cfg->sprite_texture = path;
	cfg->has_sprite = 1;
	return (0);
}
