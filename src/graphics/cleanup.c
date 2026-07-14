/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/11 16:00:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"
#include <stdlib.h>

void	destroy_texture(t_game *game, t_texture *tex)
{
	if (tex->pixels)
		free(tex->pixels);
	tex->pixels = NULL;
	if (tex->img.ptr)
		mlx_destroy_image(game->mlx, tex->img.ptr);
	tex->img.ptr = NULL;
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
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
}

void	game_cleanup(t_game *game)
{
	int	i;

	if (!game)
		return ;
	if (game->has_sprites)
	{
		i = 0;
		while (i < game->num_sprite_frames)
		{
			destroy_texture(game, &game->sprite_frames[i]);
			i++;
		}
		free(game->sprite_frames);
	}
	if (game->sprites)
		free(game->sprites);
	if (game->has_door_tex)
		destroy_texture(game, &game->door_tex);
	destroy_wall_textures(game);
	if (game->z_buffer)
		free(game->z_buffer);
	destroy_mlx_resources(game);
}
