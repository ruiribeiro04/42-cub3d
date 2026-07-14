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

static int	door_toggle(t_game *game, int mx, int my)
{
	t_map	*map;
	char	cell;

	map = &game->config->map;
	if (!map_in_bounds(map, mx, my))
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
	int			fx;
	int			fy;

	p = &game->config->player;
	fx = (int)(p->x + p->dir_x);
	fy = (int)(p->y + p->dir_y);
	door_toggle(game, fx, fy);
}
