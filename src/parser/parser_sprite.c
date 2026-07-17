/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/15 14:45:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser_internal.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <libft.h>

/*
 * Validates the sprite base path. The runtime will append "01.xpm".."10.xpm"
 * (up to 6 chars + extension) so we cap the base at SPRITE_PATH_MAX to leave
 * room in the fixed-size path buffer used by init_sprites_bonus.c.
 */
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
