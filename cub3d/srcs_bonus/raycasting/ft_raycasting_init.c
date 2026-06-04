/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:22:35 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_raycasting_calc_delta(t_game *game)
{
	if (game->ray.dir_x == 0)
		game->ray.delta_x = 1e30;
	else
		game->ray.delta_x = fabs(1.0 / game->ray.dir_x);
	if (game->ray.dir_y == 0)
		game->ray.delta_y = 1e30;
	else
		game->ray.delta_y = fabs(1.0 / game->ray.dir_y);
}

void	ft_raycasting_init_ray(t_game *game, float angle)
{
	game->ray.dir_x = cos(angle);
	game->ray.dir_y = sin(angle);
	game->ray.map_x = (int)(game->player.x / BLOCK);
	game->ray.map_y = (int)(game->player.y / BLOCK);
	game->ray.side = 0;
	ft_raycasting_calc_delta(game);
}

static void	ft_raycasting_calc_step_x(t_game *game)
{
	float	player_cell_x;

	player_cell_x = game->player.x / BLOCK;
	if (game->ray.dir_x < 0)
	{
		game->ray.step_x = -1;
		game->ray.side_x = (player_cell_x - game->ray.map_x)
			* game->ray.delta_x;
	}
	else
	{
		game->ray.step_x = 1;
		game->ray.side_x = (game->ray.map_x + 1.0 - player_cell_x)
			* game->ray.delta_x;
	}
}

static void	ft_raycasting_calc_step_y(t_game *game)
{
	float	player_cell_y;

	player_cell_y = game->player.y / BLOCK;
	if (game->ray.dir_y < 0)
	{
		game->ray.step_y = -1;
		game->ray.side_y = (player_cell_y - game->ray.map_y)
			* game->ray.delta_y;
	}
	else
	{
		game->ray.step_y = 1;
		game->ray.side_y = (game->ray.map_y + 1.0 - player_cell_y)
			* game->ray.delta_y;
	}
}

void	ft_raycasting_calc_step(t_game *game)
{
	ft_raycasting_calc_step_x(game);
	ft_raycasting_calc_step_y(game);
}
