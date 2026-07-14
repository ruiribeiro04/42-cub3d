/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/11 16:00:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "sprites.h"
#include "../graphics/graphics.h"
#include <stdlib.h>

static void	copy_positions(t_game *game, t_config *cfg)
{
	int	i;

	i = 0;
	while (i < cfg->num_sprites)
	{
		game->sprites[i].x = cfg->sprite_positions[i].x;
		game->sprites[i].y = cfg->sprite_positions[i].y;
		game->sprites[i].distance = 0.0;
		i++;
	}
}

int	sprites_init(t_game *game)
{
	t_config	*cfg;

	cfg = game->config;
	if (!cfg->has_sprite || cfg->num_sprites == 0)
	{
		game->has_sprites = 0;
		return (0);
	}
	game->sprites = (t_sprite *)malloc(
			sizeof(t_sprite) * cfg->num_sprites);
	if (!game->sprites)
		return (cub_error_int("Failed to alloc sprites"));
	copy_positions(game, cfg);
	game->num_sprites = cfg->num_sprites;
	game->has_sprites = 1;
	game->sprite_frame = 0;
	game->sprite_anim_counter = 0;
	return (0);
}
