/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doors_logic.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:20:43 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_doors_logic.c
 * @brief Door open/close logic and state management.
 */

#include "cub3d.h"

static t_door	*ft_get_target_door(t_game *game, float dir_x, float dir_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)((game->player.x + dir_x * BLOCK * DOOR_INTERACT_DIST)
			/ BLOCK);
	map_y = (int)((game->player.y + dir_y * BLOCK * DOOR_INTERACT_DIST)
			/ BLOCK);
	if (map_y < 0 || map_y >= game->map_height || map_x < 0
		|| map_x >= game->map_width)
		return (NULL);
	return (game->door_map[map_y][map_x]);
}

static int	ft_is_facing_door(t_game *game, t_door *door, float dir_x,
		float dir_y)
{
	float	dx;
	float	dy;
	float	dist;
	float	dot;

	dx = (door->x * BLOCK + BLOCK / 2) - game->player.x;
	dy = (door->y * BLOCK + BLOCK / 2) - game->player.y;
	dist = sqrt(dx * dx + dy * dy);
	if (dist == 0)
		return (0);
	dot = (dx * dir_x + dy * dir_y) / dist;
	if (dot > 0.2f)
		return (1);
	return (0);
}

/**
 * @ingroup graphics
 */
void	ft_handle_door_interaction(t_game *game)
{
	t_door	*door;
	float	dir_x;
	float	dir_y;

	if (!game->door_map)
		return ;
	dir_x = cos(game->player.angle);
	dir_y = sin(game->player.angle);
	door = ft_get_target_door(game, dir_x, dir_y);
	if (door && ft_is_facing_door(game, door, dir_x, dir_y))
	{
		if (door->state == DOOR_CLOSED)
			door->state = DOOR_OPENING;
		else if (door->state == DOOR_OPEN)
			door->state = DOOR_CLOSING;
	}
}

static void	ft_handle_closing(t_door *door, int p_x, int p_y, double dt)
{
	if (p_x == door->x && p_y == door->y)
		door->state = DOOR_OPENING;
	else
	{
		door->progress -= DOOR_SPEED * dt;
		if (door->progress <= 0.0f)
		{
			door->progress = 0.0f;
			/**
			 * @ingroup graphics
			 */
			door->state = DOOR_CLOSED;
		}
	}
}

void	ft_update_doors(t_game *game, double delta_time)
{
	int	i;
	int	p_x;
	int	p_y;

	p_x = (int)(game->player.x / BLOCK);
	p_y = (int)(game->player.y / BLOCK);
	i = 0;
	while (i < game->door_count)
	{
		if (game->doors[i].state == DOOR_OPENING)
		{
			game->doors[i].progress += DOOR_SPEED * delta_time;
			if (game->doors[i].progress >= 1.0f)
			{
				game->doors[i].progress = 1.0f;
				game->doors[i].state = DOOR_OPEN;
			}
		}
		else if (game->doors[i].state == DOOR_CLOSING)
			ft_handle_closing(&game->doors[i], p_x, p_y, delta_time);
		i++;
	}
}
