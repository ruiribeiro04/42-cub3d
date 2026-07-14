/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/11 16:00:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "bonus.h"
#include "../graphics/graphics.h"

static int	in_bounds(t_map *map, int mx, int my)
{
	if (my < 0 || my >= map->height)
		return (0);
	if (mx < 0 || mx >= map->width)
		return (0);
	return (1);
}

int	door_toggle(t_game *game, int mx, int my)
{
	t_map	*map;
	char	cell;

	map = &game->config->map;
	if (!in_bounds(map, mx, my))
		return (0);
	cell = map->grid[my][mx];
	if (cell == 'D')
		map->grid[my][mx] = 'O';
	else if (cell == 'O')
		map->grid[my][mx] = 'D';
	else
		return (0);
	return (1);
}

void	door_try_front(t_game *game)
{
	t_player	*p;
	int			px;
	int			py;

	p = &game->config->player;
	px = (int)p->x;
	py = (int)p->y;
	if (door_toggle(game, px + 1, py))
		return ;
	if (door_toggle(game, px - 1, py))
		return ;
	if (door_toggle(game, px, py + 1))
		return ;
	if (door_toggle(game, px, py - 1))
		return ;
}
