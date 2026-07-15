/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/15 14:45:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"
#include <stdlib.h>

/*
 * Idempotent: safe to call on a zeroed t_texture or to call twice.
 * Frees the pixel cache, destroys the mlx image, and zeroes both.
 */
void	destroy_texture(t_game *game, t_texture *tex)
{
	if (tex->pixels)
		free(tex->pixels);
	tex->pixels = NULL;
	if (tex->img.ptr)
		mlx_destroy_image(game->mlx, tex->img.ptr);
	tex->img.ptr = NULL;
}

/*
 * Frees the sprite frame array, destroying up to `count` textures.
 * Returns -1 so callers in error paths can `return (free_sprite_frames(...))`.
 */
int	free_sprite_frames(t_game *game, int count)
{
	int	i;

	i = 0;
	while (i < count)
		destroy_texture(game, &game->sprite_frames[i++]);
	free(game->sprite_frames);
	game->sprite_frames = NULL;
	game->num_sprite_frames = 0;
	return (-1);
}

static void	destroy_wall_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		destroy_texture(game, &game->tex[i]);
		i++;
	}
}

static void	destroy_mlx_resources(t_game *game)
{
	if (game->frame.ptr)
		mlx_destroy_image(game->mlx, game->frame.ptr);
	game->frame.ptr = NULL;
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	game->win = NULL;
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}

void	game_cleanup(t_game *game)
{
	if (!game)
		return ;
	if (game->sprite_frames)
		free_sprite_frames(game, game->num_sprite_frames);
	if (game->sprites)
		free(game->sprites);
	game->sprites = NULL;
	if (game->door_tex.img.ptr)
		destroy_texture(game, &game->door_tex);
	destroy_wall_textures(game);
	if (game->z_buffer)
		free(game->z_buffer);
	game->z_buffer = NULL;
	destroy_mlx_resources(game);
}
