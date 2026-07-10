/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting_dda.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:20:11 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_raycasting_dda.c
 * @brief DDA raycasting algorithm implementation.
 */

#include "cub3d.h"

void	ft_raycasting_calc_wall_x(t_game *game)
{
	float	wall_x;

	if (game->ray.side == 0)
		wall_x = game->player.y + game->ray.perp_dist * game->ray.dir_y;
	else
		wall_x = game->player.x + game->ray.perp_dist * game->ray.dir_x;
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
	/**
	 * @ingroup raycasting
	 */
	if (y < 0 || y >= game->map_height)
		return (1);
	return (game->map[y][x] == '1');
}

void	ft_raycasting_perform_dda(t_game *game)
{
	int	hit;

	hit = 0;
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
			/**
			 * @ingroup raycasting
			 */
			game->ray.side = 1;
		}
		if (ft_raycasting_is_wall(game, game->ray.map_x, game->ray.map_y))
			hit = 1;
	}
}

void	ft_raycasting_calc_wall_height(t_game *game)
{
	if (game->ray.side == 0)
		game->ray.perp_dist = (game->ray.side_x - game->ray.delta_x);
	else
		game->ray.perp_dist = (game->ray.side_y - game->ray.delta_y);
	ft_raycasting_calc_wall_x(game);
	game->ray.wall_height = (int)(HEIGHT / game->ray.perp_dist);
	game->ray.draw_start = -game->ray.wall_height / 2 + HEIGHT / 2;
	if (game->ray.draw_start < 0)
		game->ray.draw_start = 0;
	game->ray.draw_end = game->ray.wall_height / 2 + HEIGHT / 2;
	if (game->ray.draw_end >= HEIGHT)
		game->ray.draw_end = HEIGHT - 1;
}
