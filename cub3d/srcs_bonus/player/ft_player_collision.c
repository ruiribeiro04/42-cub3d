/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player_collision.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:22:15 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_player_collision.c
 * @brief Player wall collision detection.
 */

#include "cub3d.h"

static int	ft_is_blocked_tile(t_game *game, int map_x, int map_y)
{
	t_door	*door;

	if (map_x < 0 || map_x >= game->map_width)
		return (1);
	if (map_y < 0 || map_y >= game->map_height)
		return (1);
	if (game->map[map_y][map_x] == '1')
		return (1);
	if (game->map[map_y][map_x] == 'D')
	{
		door = game->door_map[map_y][map_x];
		if (door && door->state != DOOR_OPEN)
			return (1);
	}
	return (0);
}

/**
 * @ingroup player
 */
int	ft_player_check_collisions(t_game *game, float x, float y)
{
	int	map_x;
	int	map_y;
	int	i;
	int	j;

	if (!game->door_map)
		return (0);
	i = -1;
	while (i <= 1)
	{
		j = -1;
		while (j <= 1)
		{
			map_x = (int)(x + i * COLLISION_MARGIN);
			map_y = (int)(y + j * COLLISION_MARGIN);
			if (ft_is_blocked_tile(game, map_x, map_y))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
