/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/15 14:45:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"
#include "sprites.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <libft.h>

/*
 * Builds path "<base>NN.xpm" and tries to load it as frame idx.
 * Returns 1 if loaded, 0 if file missing (end of sequence), -1 on error.
 */
static int	load_one_frame(t_game *game, t_config *cfg, int idx)
{
	char	path[SPRITE_PATH_MAX];
	char	num_str[3];

	ft_strlcpy(path, cfg->sprite_texture, sizeof(path));
	if (idx + 1 < 10)
	{
		num_str[0] = '0';
		num_str[1] = '0' + (idx + 1);
	}
	else
	{
		num_str[0] = '0' + ((idx + 1) / 10);
		num_str[1] = '0' + ((idx + 1) % 10);
	}
	num_str[2] = '\0';
	ft_strlcat(path, num_str, sizeof(path));
	ft_strlcat(path, ".xpm", sizeof(path));
	if (!ft_path_readable(path))
		return (0);
	if (ft_load_texture(game, &game->sprite_frames[idx], path) < 0)
		return (-1);
	return (1);
}

static int	alloc_sprite_frames(t_game *game, t_config *cfg)
{
	if (ft_strlen(cfg->sprite_texture) > SPRITE_PATH_MAX - 16)
		return (ft_cub_error_int("Sprite texture path too long"));
	game->sprite_frames = (t_texture *)malloc(
			sizeof(t_texture) * MAX_SPRITE_FRAMES);
	if (!game->sprite_frames)
		return (ft_cub_error_int("Failed to alloc sprite frames"));
	ft_bzero(game->sprite_frames, sizeof(t_texture) * MAX_SPRITE_FRAMES);
	return (0);
}

static int	load_sprite_frames(t_game *game, t_config *cfg)
{
	int	i;
	int	ret;

	if (alloc_sprite_frames(game, cfg) < 0)
		return (-1);
	i = 0;
	while (i < MAX_SPRITE_FRAMES)
	{
		ret = load_one_frame(game, cfg, i);
		if (ret < 0)
			return (ft_free_sprite_frames(game, i));
		if (ret == 0)
			break ;
		i++;
	}
	game->num_sprite_frames = i;
	if (i == 0)
	{
		ft_free_sprite_frames(game, 0);
		return (ft_cub_error_int("No sprite frames found"));
	}
	return (0);
}

int	ft_init_sprites_if_present(t_game *game, t_config *cfg)
{
	if (!cfg->has_sprite)
		return (0);
	if (load_sprite_frames(game, cfg) < 0)
		return (-1);
	if (sprites_init(game) < 0)
	{
		ft_free_sprite_frames(game, game->num_sprite_frames);
		return (-1);
	}
	return (0);
}

int	ft_init_optional_textures(t_game *game, t_config *cfg)
{
	game->has_door_tex = 0;
	if (cfg->has_door_texture)
	{
		if (ft_load_texture(game, &game->door_tex,
				cfg->door_texture) < 0)
			return (ft_cub_error_int("Failed to load door tex"));
		game->has_door_tex = 1;
	}
	return (ft_init_sprites_if_present(game, cfg));
}
