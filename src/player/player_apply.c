/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_apply.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/11 16:00:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "player.h"
#include "../graphics/graphics.h"

static int	is_wall(t_map *map, double x, double y)
{
	int	mx;
	int	my;

	mx = (int)x;
	my = (int)y;
	if (!map_in_bounds(map, mx, my))
		return (1);
	return (map->grid[my][mx] == '1' || map->grid[my][mx] == 'D');
}

static int	check_corners(t_map *map, double x, double y)
{
	double	m;

	m = COLLISION_MARGIN;
	if (is_wall(map, x + m, y + m))
		return (1);
	if (is_wall(map, x - m, y + m))
		return (1);
	if (is_wall(map, x + m, y - m))
		return (1);
	if (is_wall(map, x - m, y - m))
		return (1);
	return (0);
}

static void	try_move_x(t_player *p, t_map *map, double dx)
{
	double	margin;

	margin = COLLISION_MARGIN;
	if (dx < 0)
		margin = -margin;
	if (!is_wall(map, p->x + dx + margin, p->y)
		&& !check_corners(map, p->x + dx, p->y))
		p->x += dx;
}

static void	try_move_y(t_player *p, t_map *map, double dy)
{
	double	margin;

	margin = COLLISION_MARGIN;
	if (dy < 0)
		margin = -margin;
	if (!is_wall(map, p->x, p->y + dy + margin)
		&& !check_corners(map, p->x, p->y + dy))
		p->y += dy;
}

void	apply_movement(t_game *game, t_player *p, t_keys *k)
{
	if (k->w)
	{
		try_move_x(p, &game->config->map, p->dir_x * MOVE_SPEED);
		try_move_y(p, &game->config->map, p->dir_y * MOVE_SPEED);
	}
	if (k->s)
	{
		try_move_x(p, &game->config->map, -p->dir_x * MOVE_SPEED);
		try_move_y(p, &game->config->map, -p->dir_y * MOVE_SPEED);
	}
	if (k->a)
	{
		try_move_x(p, &game->config->map, -p->plane_x * MOVE_SPEED);
		try_move_y(p, &game->config->map, -p->plane_y * MOVE_SPEED);
	}
	if (k->d)
	{
		try_move_x(p, &game->config->map, p->plane_x * MOVE_SPEED);
		try_move_y(p, &game->config->map, p->plane_y * MOVE_SPEED);
	}
}
