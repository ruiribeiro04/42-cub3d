/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_apply.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/15 14:45:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"
#include "player.h"


static int	is_wall(t_map *map, double x, double y)
{
	int	mx;
	int	my;

	if (x < 0 || y < 0)
		return (1);
	mx = (int)x;
	my = (int)y;
	if (my < 0 || my >= map->height || mx < 0 || mx >= map->width)
		return (1);
	return (map->grid[my][mx] == '1' || map->grid[my][mx] == 'D' ||
		map->grid[my][mx] == ' ');
}


static void	try_move_x(t_player *p, t_map *map, double dx)
{
	double	margin;

	margin = COLLISION_MARGIN;
	if (dx < 0)
		margin = -margin;
	if (is_wall(map, p->x, p->y))
		margin = 0;
	if (!is_wall(map, p->x + dx + margin, p->y))
		p->x += dx;
}

static void	try_move_y(t_player *p, t_map *map, double dy)
{
	double	margin;

	margin = COLLISION_MARGIN;
	if (dy < 0)
		margin = -margin;
	if (is_wall(map, p->x, p->y))
		margin = 0;
	if (!is_wall(map, p->x, p->y + dy + margin))
		p->y += dy;
}

void	ft_apply_movement(t_game *game, t_player *p, t_keys *k)
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
