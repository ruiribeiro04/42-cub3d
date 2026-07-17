/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/15 14:45:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"
#include "bonus.h"

/*
 * Toggles a door cell between 'D' (closed) and 'O' (open).
 * Returns 1 if a door was toggled, 0 otherwise (cell not a door / OOB).
 * `static` because only ft_door_toggle_safe in this file calls it.
 */
static int	ft_door_toggle(t_game *game, int mx, int my)
{
	t_map	*map;
	char	cell;

	map = &game->config->map;
	if (!ft_map_in_bounds(map, mx, my))
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

static int	ft_player_too_close(t_player *p, int mx, int my)
{
	double	dx;
	double	dy;

	dx = p->x - ((double)mx + 0.5);
	dy = p->y - ((double)my + 0.5);
	return (dx * dx + dy * dy < 1.0);
}

/*
 * Toggles a door, but refuses to CLOSE it if the player is too close
 * (prevents the player from being trapped inside a closing door).
 */
static int	ft_door_toggle_safe(t_game *game, int mx, int my)
{
	t_map		*map;
	char		cell;
	t_player	*p;

	map = &game->config->map;
	if (!ft_map_in_bounds(map, mx, my))
		return (0);
	cell = map->grid[my][mx];
	p = &game->config->player;
	if (cell == 'O' && ft_player_too_close(p, mx, my))
		return (0);
	return (ft_door_toggle(game, mx, my));
}

void	ft_door_try_front(t_game *game)
{
	t_player	*p;
	int			px;
	int			py;
	int			dx;
	int			dy;

	p = &game->config->player;
	px = (int)p->x;
	py = (int)p->y;
	dy = -2;
	while (dy <= 2)
	{
		dx = -2;
		while (dx <= 2)
		{
			if (ft_door_toggle_safe(game, px + dx, py + dy))
				return ;
			dx++;
		}
		dy++;
	}
}
