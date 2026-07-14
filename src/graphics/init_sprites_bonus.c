/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/14 16:00:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"
#include "../bonus/sprites.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <libft.h>

/* Builds path: base + "01.xpm" etc. */
static void	build_path(char *dst, size_t size,
					const char *base, int num)
{
	char	num_str[3];

	ft_strlcpy(dst, base, size);
	if (num < 10)
	{
		num_str[0] = '0';
		num_str[1] = '0' + num;
	}
	else
	{
		num_str[0] = '0' + (num / 10);
		num_str[1] = '0' + (num % 10);
	}
	num_str[2] = '\0';
	ft_strlcat(dst, num_str, size);
	ft_strlcat(dst, ".xpm", size);
}

/* Loads all sprite frames (sprite01.xpm, sprite02.xpm...). */
static int	load_sprite_frames(t_game *game, t_config *cfg)
{
	char	path[256];
	int		i;

	game->sprite_frames = (t_texture *)malloc(
			sizeof(t_texture) * MAX_SPRITE_FRAMES);
	if (!game->sprite_frames)
		return (cub_error_int("Failed to alloc sprite frames"));
	ft_bzero(game->sprite_frames, sizeof(t_texture) * MAX_SPRITE_FRAMES);
	i = 0;
	while (i < MAX_SPRITE_FRAMES)
	{
		build_path(path, sizeof(path), cfg->sprite_texture, i + 1);
		if (!path_readable(path))
			break ;
		if (load_texture(game, &game->sprite_frames[i], path) < 0)
			return (free_sprite_frames(game, i));
		i++;
	}
	game->num_sprite_frames = i;
	if (i == 0)
	{
		free_sprite_frames(game, 0);
		return (cub_error_int("No sprite frames found"));
	}
	return (0);
}

int	init_sprites_if_present(t_game *game, t_config *cfg)
{
	if (!cfg->has_sprite)
		return (0);
	if (load_sprite_frames(game, cfg) < 0)
		return (-1);
	if (sprites_init(game) < 0)
		return (-1);
	return (0);
}

int	init_optional_textures(t_game *game, t_config *cfg)
{
	game->has_door_tex = 0;
	if (cfg->has_door_texture)
	{
		if (load_texture(game, &game->door_tex,
				cfg->door_texture) < 0)
			return (cub_error_int("Failed to load door tex"));
		game->has_door_tex = 1;
	}
	return (init_sprites_if_present(game, cfg));
}
