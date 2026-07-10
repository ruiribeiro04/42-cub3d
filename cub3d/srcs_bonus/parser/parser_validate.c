/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:22:10 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_validate.c
 * @brief Validate the parsed map for the bonus tree.
 */

#include "cub3d.h"

/**
* @brief Checks if a character is valid on the map.
* 
* Valid characters are:
* - ‘0’: Empty space (walkable)
* - ‘1’: Wall
* - ‘ ’: Space (outside the playable map)
* - ‘N’, ‘S’, ‘E’, ‘W’: Player spawn positions
* 
* @param c Character to check.
* @return int 1 if valid, 0 if invalid.
*/
static int	is_valid_char(char c)
{
	if (c == '0' || c == '1' || c == ' ')
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	if (c == 'D' || c == 'A' || c == '2')
		return (1);
	return (0);
}

static int	check_row_chars(char **map, int y)
{
	int	x;

	x = 0;
	while (map[y][x])
	{
		if (!is_valid_char(map[y][x]))
		{
			ft_putstr_fd("Error\nInvalid character '", 2);
			ft_putchar_fd(map[y][x], 2);
			ft_putstr_fd("' in map\n", 2);
			return (1);
		}
		x++;
	}
	return (0);
}

/**
 * @brief Validates all characters in the map.
 * 
 * Traverses the entire map checking if all characters
 * are valid. Prints an error message with the invalid character
 * if found.
 * 
 * @param game Pointer to the game structure.
 * @return int 0 if all characters are valid, 1 if there are invalid ones.
  * @ingroup parser
 */
int	ft_validate_map_chars(t_game *game)
{
	int	y;

	y = 0;
	while (game->map[y])
	{
		if (check_row_chars(game->map, y))
			return (1);
		y++;
	}
	return (0);
}

/**
* @brief Prints a boundary error message.
* 
* Auxiliary function that prints detailed information about
* where the map is not correctly closed.
* 
* @param game Pointer to the game structure.
* @param y Index of the row where the error occurred.
* @param x Index of the column where the error occurred.
* @return int Always returns 1 (error).
* 
* @warning This function only works correctly for indexes < 10
*          due to the simple conversion with ‘0’ + y.
*/
static int	print_boundary_error(t_game *game, int y, int x)
{
	ft_putstr_fd("Error\nMap not properly closed at row ", 2);
	ft_putchar_fd('0' + y, 2);
	ft_putstr_fd(" col ", 2);
	ft_putchar_fd('0' + x, 2);
	ft_putstr_fd(" char '", 2);
	ft_putchar_fd(game->map[y][x], 2);
	ft_putstr_fd("'\n", 2);
	return (1);
}

/**
 * @brief Validates whether the map is completely closed.
 *
 * Traverses all cells in the map and checks whether the map is
 * correctly closed by walls, with no holes or openings
 * that would allow the player to "escape."
 *
 * @param game Pointer to the game structure.
 * @return int 0 if the map is closed, 1 if there are problems.
 * @ingroup parser
 */
int	ft_validate_map_closed(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (validate_row_boundaries(game, y, x))
				return (print_boundary_error(game, y, x));
			if (validate_space_neighbors(game, y, x))
			{
				ft_putstr_fd("Error\nSpace adjacent to open area\n", 2);
				return (1);
			}
			if (validate_overhangs(game, y, x))
			{
				ft_putstr_fd("Error\nMap cell overhangs adjacent row\n", 2);
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}
