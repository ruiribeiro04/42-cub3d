/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 14:50:20 by ruiferna          #+#    #+#             */
/*   Updated: 2026/07/17 17:33:24 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

int	ft_init_sprites_if_present(t_game *game, t_config *cfg)
{
	(void)game;
	(void)cfg;
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
