/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:53:06 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_minimap.c
 * @brief Render the minimap overlay on screen.
 */

#include "cub3d.h"

static void	ft_draw_player_marker(t_game *game, t_point *draw_pos)
{
	draw_pos->x = MAP_OFFSET_X + ((int)(game->player.x / BLOCK) * MAP_TILE);
	draw_pos->y = MAP_OFFSET_Y + ((int)(game->player.y / BLOCK) * MAP_TILE);
	ft_draw_rect(game, *draw_pos, MAP_TILE, MAP_COLOR_PLAYER);
}

/**
 * @ingroup graphics
 */
void	ft_draw_minimap(t_game *game)
{
	t_point	draw_pos;
	int		x;
	int		y;
	int		current_len;

	y = 0;
	while (y < game->map_height)
	{
		current_len = ft_strlen(game->map[y]);
		x = 0;
		while (x < game->map_width)
		{
			draw_pos.x = MAP_OFFSET_X + (x * MAP_TILE);
			draw_pos.y = MAP_OFFSET_Y + (y * MAP_TILE);
			if (x < current_len && game->map[y][x] == '1')
				ft_draw_rect(game, draw_pos, MAP_TILE, MAP_COLOR_WALL);
			else if (x < current_len && game->map[y][x] == 'D')
				ft_draw_rect(game, draw_pos, MAP_TILE, MAP_COLOR_DOOR);
			else
				ft_draw_rect(game, draw_pos, MAP_TILE, MAP_COLOR_BG);
			x++;
		}
		y++;
	}
	/* Se apagarmos o (int), o mapa fica fluido,
	mas depois tem o bug de passar pelas paredes */
	draw_pos.x = MAP_OFFSET_X + ((int)game->player.x * MAP_TILE);
	draw_pos.y = MAP_OFFSET_Y + ((int)game->player.y * MAP_TILE);
	ft_draw_rect(game, draw_pos, MAP_TILE, MAP_COLOR_PLAYER);
}
