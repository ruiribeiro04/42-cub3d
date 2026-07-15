/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/15 14:45:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

/*
 * Mandatory stub: sprite initialization is a bonus-only feature.
 * The bonus build swaps this file for init_sprites_bonus.c which loads
 * sprite frames and calls sprites_init().
 */
int	init_sprites_if_present(t_game *game, t_config *cfg)
{
	(void)game;
	(void)cfg;
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
