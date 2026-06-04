/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:21:54 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_player.c
 * @brief Initialize the player position and orientation from the map.
 */

#include "cub3d.h"

/**
* @brief Sets the player's initial angle based on the spawn direction.
* 
* Converts the cardinal direction (N, S, E, W) to radians:
* - N: 270° (3pi/2) - facing up
* - S: 90° (pi/2) - facing down
* - E: 0° - facing right
* - W: 180° (pi) - facing left
* 
* @param game Pointer to the game structure.
* @param y Y coordinate of the spawn position.
* @param x X coordinate of the spawn position.
*/
static void	set_player_angle(t_game *game, int y, int x)
{
	if (game->map[y][x] == 'N')
		game->player.angle = 3 * PI / 2;
	else if (game->map[y][x] == 'S')
		game->player.angle = PI / 2;
	else if (game->map[y][x] == 'E')
		game->player.angle = 0;
	else if (game->map[y][x] == 'W')
		game->player.angle = PI;
}

/**
* @brief Searches for the player's spawn position on the map.
* 
* Scans the entire map looking for spawn characters (N, S, E, W),
* saves the position found, sets the angle, and replaces the
* character with ‘0’. Counts the number of spawns for validation.
* 
* @param game Pointer to the game structure.
* @param spawn_x Pointer to store the X coordinate of the spawn.
* @param spawn_y Pointer to store the Y coordinate of the spawn.
* @param spawn_count Pointer to the counter of spawns found.
*/
static void	find_spawn_position(t_game *game, int *spawn_x,
	int *spawn_y, int *spawn_count)
{
	int	y;
	int	x;

	*spawn_count = 0;
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'N' || game->map[y][x] == 'S'
				|| game->map[y][x] == 'E' || game->map[y][x] == 'W')
			{
				*spawn_x = x;
				*spawn_y = y;
				(*spawn_count)++;
				set_player_angle(game, y, x);
				game->map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
}

/**
* @brief Initializes the player based on map information.
* 
* Finds the spawn position, validates that there is exactly one,
* and calculates the player's position in pixels (centered on the block).
* 
* @param game Pointer to the game structure.
* 
* @note The position is calculated by adding 0.5 to the index and multiplying
*       by BLOCK to center the player in the cell.
 * @ingroup parser
 */
int	ft_init_player_from_map(t_game *game)
{
	int	spawn_count;
	int	spawn_x;
	int	spawn_y;

	find_spawn_position(game, &spawn_x, &spawn_y, &spawn_count);
	if (spawn_count == 0)
	{
		ft_putstr_fd("Error\nNo player spawn position found\n", 2);
		return (1);
	}
	if (spawn_count > 1)
	{
		ft_putstr_fd("Error\nMultiple player spawn positions found\n", 2);
		return (1);
	}
	game->player.x = (spawn_x + 0.5) * BLOCK;
	game->player.y = (spawn_y + 0.5) * BLOCK;
	return (0);
}
