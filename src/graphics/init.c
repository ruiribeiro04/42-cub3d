/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/11 16:00:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"
#include <stdlib.h>

int	color_to_int(t_color c, int endian)
{
	if (endian == 0)
		return ((c.r << 16) | (c.g << 8) | c.b);
	return ((c.b << 16) | (c.g << 8) | c.r);
}

static void	init_keys(t_keys *keys)
{
	keys->w = 0;
	keys->a = 0;
	keys->s = 0;
	keys->d = 0;
	keys->left = 0;
	keys->right = 0;
}

static int	load_all_textures(t_game *game, t_config *cfg)
{
	if (load_texture(game, &game->tex[TEX_NORTH], cfg->textures.north) < 0)
		return (-1);
	if (load_texture(game, &game->tex[TEX_SOUTH], cfg->textures.south) < 0)
		return (-1);
	if (load_texture(game, &game->tex[TEX_WEST], cfg->textures.west) < 0)
		return (-1);
	if (load_texture(game, &game->tex[TEX_EAST], cfg->textures.east) < 0)
		return (-1);
	return (0);
}

static int	init_frame(t_game *game)
{
	game->frame.ptr = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->frame.ptr)
		return (-1);
	game->frame.data = mlx_get_data_addr(game->frame.ptr,
			&game->frame.bpp, &game->frame.line_len,
			&game->frame.endian);
	if (!game->frame.data)
		return (-1);
	game->frame.width = WIN_WIDTH;
	game->frame.height = WIN_HEIGHT;
	return (0);
}

int	game_init(t_game *game, t_config *config)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (cub_error_int("mlx_init failed"));
	game->win = mlx_new_window(game->mlx, WIN_WIDTH,
			WIN_HEIGHT, "cub3D");
	if (!game->win)
		return (cub_error_int("mlx_new_window failed"));
	if (init_frame(game) < 0)
		return (cub_error_int("Failed to create frame image"));
	game->config = config;
	game->floor_color = color_to_int(config->floor, game->frame.endian);
	game->ceiling_color = color_to_int(config->ceiling, game->frame.endian);
	init_keys(&game->keys);
	game->z_buffer = (double *)malloc(sizeof(double) * WIN_WIDTH);
	if (!game->z_buffer)
		return (cub_error_int("Failed to alloc z_buffer"));
	if (load_all_textures(game, config) < 0)
		return (cub_error_int("Failed to load textures"));
	if (init_optional_textures(game, config) < 0)
		return (-1);
	return (0);
}
