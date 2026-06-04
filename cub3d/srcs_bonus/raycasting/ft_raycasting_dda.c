/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting_dda.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:22:28 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_raycasting_dda.c
 * @brief DDA raycasting algorithm implementation.
 */

#include "cub3d.h"

/**
 * @ingroup raycasting
 */
void	ft_raycasting_calc_wall_x(t_game *game, float eucl_dist)
{
	float	wall_x;

	if (game->ray.side == 0)
		wall_x = (game->player.y / BLOCK) + eucl_dist * game->ray.dir_y;
	else
		wall_x = (game->player.x / BLOCK) + eucl_dist * game->ray.dir_x;
	wall_x -= floor(wall_x);
	/**
	 * @ingroup raycasting
	 */
	game->ray.wall_x = wall_x;
}

int	ft_raycasting_is_wall(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map_width)
		return (1);
	if (y < 0 || y >= game->map_height)
		return (1);
	return (game->map[y][x] == '1');
}

static int	ft_raycasting_check_door(t_game *game)
{
	t_door	*door;

	if (!game->door_map)
		return (0);
	door = game->door_map[game->ray.map_y][game->ray.map_x];
	/**
	 * @ingroup raycasting
	 */
	if (!door || door->state == DOOR_OPEN)
		return (0);
	game->ray.hit_door = door;
	return (1);
}

void	ft_raycasting_perform_dda(t_game *game)
{
	int	hit;

	hit = 0;
	game->ray.hit_door = NULL;
	while (hit == 0)
	{
		if (game->ray.side_x < game->ray.side_y)
		{
			game->ray.side_x += game->ray.delta_x;
			game->ray.map_x += game->ray.step_x;
			game->ray.side = 0;
		}
		else
		{
			game->ray.side_y += game->ray.delta_y;
			game->ray.map_y += game->ray.step_y;
			game->ray.side = 1;
		}
		if (ft_raycasting_is_wall(game, game->ray.map_x, game->ray.map_y))
			hit = 1;
		/**
		 * @ingroup raycasting
		 */
		else if (game->map[game->ray.map_y][game->ray.map_x] == 'D')
			hit = ft_raycasting_check_door(game);
	}
}

void	ft_raycasting_calc_wall_height(t_game *game, float angle)
{
	float	eucl_dist;
	float	perp_dist;
	float	fish_eye;

	if (game->ray.side == 0)
		eucl_dist = game->ray.side_x - game->ray.delta_x;
	else
		eucl_dist = game->ray.side_y - game->ray.delta_y;
	ft_raycasting_calc_wall_x(game, eucl_dist);
	fish_eye = cos(angle - game->player.angle);
	perp_dist = eucl_dist * fish_eye;
	game->ray.perp_dist = perp_dist * BLOCK;
	if (game->ray.perp_dist < 1.0f)
		game->ray.perp_dist = 1.0f;
	game->ray.wall_height = (int)((BLOCK / game->ray.perp_dist) * (WIDTH / 2));
	game->ray.draw_start = (HEIGHT - game->ray.wall_height) / 2;
	game->ray.draw_end = game->ray.draw_start + game->ray.wall_height;
}
