/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 19:31:40 by ruiferna          #+#    #+#             */
/*   Updated: 2026/07/17 17:17:43 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include <stdlib.h>


void	ft_destroy_texture(t_game *game, t_texture *tex)
{
	if (tex->pixels)
		free(tex->pixels);
	tex->pixels = NULL;
	if (tex->img.ptr)
		mlx_destroy_image(game->mlx, tex->img.ptr);
	tex->img.ptr = NULL;
}


int	ft_free_sprite_frames(t_game *game, int count)
{
	int	i;

	i = 0;
	while (i < count)
		ft_destroy_texture(game, &game->sprite_frames[i++]);
	free(game->sprite_frames);
	game->sprite_frames = NULL;
	game->num_sprite_frames = 0;
	return (-1);
}

static void	ft_destroy_wall_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		ft_destroy_texture(game, &game->tex[i]);
		i++;
	}
}

static void	ft_destroy_mlx_resources(t_game *game)
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

void	ft_game_cleanup(t_game *game)
{
	if (!game)
		return ;
	if (game->sprite_frames)
		ft_free_sprite_frames(game, game->num_sprite_frames);
	if (game->sprites)
		free(game->sprites);
	game->sprites = NULL;
	if (game->door_tex.img.ptr)
		ft_destroy_texture(game, &game->door_tex);
	ft_destroy_wall_textures(game);
	if (game->z_buffer)
		free(game->z_buffer);
	game->z_buffer = NULL;
	ft_destroy_mlx_resources(game);
}
