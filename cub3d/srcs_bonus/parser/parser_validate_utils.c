/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validate_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:22:06 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_validate_utils.c
 * @brief Map validation utility helpers.
 */

#include "cub3d.h"

static int	check_edge_char(char c)
{
	if (c != '1' && c != ' ' && c != 'D')
		return (1);
	return (0);
}

/**
 * @brief Validates the boundaries of a row in the map.
 *
 * Checks whether the cells at the edges (first/last row or
 * first/last column) contain only valid boundary characters
 * ('1', ' ', 'N', 'S', 'E', 'W').
 *
 * @param game Pointer to the game structure.
 * @param y Index of the row to check.
 * @param x Index of the column to check.
 * @return int 0 if valid, 1 if invalid.
 * @ingroup parser
 */
int	validate_row_boundaries(t_game *game, int y, int x)
{
	int	len;

	if (y == 0 || !game->map[y + 1])
		return (check_edge_char(game->map[y][x]));
	len = ft_strlen(game->map[y]);
	if (x == 0 || x == len - 1)
		return (check_edge_char(game->map[y][x]));
	return (0);
}

/**
 * @brief Validates whether walkable cells are not adjacent to spaces.
 * 
 * Checks whether cells with '0' or spawn (N, S, E, W) do not have
 * empty spaces (' ') as direct neighbors (up, down, left, right).
 * This ensures that the map is properly closed.
 * 
 * @param game Pointer to the game structure.
 * @param y Row index.
 * @param x Column index.
 * @return int 0 if valid, 1 if there is space adjacent to the open area.
 */
int	validate_space_neighbors(t_game *game, int y, int x)
{
	char	curr;

	curr = game->map[y][x];
	if (curr == ' ')
		return (0);
	if (curr != '0' && curr != 'N' && curr != 'S' && curr != 'E'
		&& curr != 'W' && curr != '2' && curr != 'D')
		return (0);
	if (x > 0 && game->map[y][x - 1] == ' ')
		return (1);
	if (game->map[y][x + 1] && game->map[y][x + 1] == ' ')
		return (1);
	if (y > 0 && x < (int)ft_strlen(game->map[y - 1])
		&& game->map[y - 1][x] == ' ')
		return (1);
	if (game->map[y + 1] && x < (int)ft_strlen(game->map[y + 1])
		&& game->map[y + 1][x] == ' ')
		return (1);
	return (0);
}

/**
 * @brief Validates overhangs on the map.
 * 
 * Checks for cells that extend beyond adjacent lines
 * without being walls ('1'). This prevents maps with invalid shapes
 * where walkable areas are exposed to the "void."
 * 
 * @param game Pointer to the game structure.
 * @param y Row index.
 * @param x Column index.
 * @return int 0 if valid, 1 if there is an invalid overhang.
 */
int	validate_overhangs(t_game *game, int y, int x)
{
	int	len_top;
	int	len_bottom;

	if (y > 0)
	{
		len_top = ft_strlen(game->map[y - 1]);
		if (x >= len_top && game->map[y][x] != '1')
			return (1);
	}
	if (game->map[y + 1])
	{
		len_bottom = ft_strlen(game->map[y + 1]);
		if (x >= len_bottom && game->map[y][x] != '1')
			return (1);
	}
	if (y > 0 && x < (int)ft_strlen(game->map[y]))
	{
		len_top = ft_strlen(game->map[y - 1]);
		if (len_top > (int)ft_strlen(game->map[y])
			&& x == (int)ft_strlen(game->map[y]) - 1
			&& game->map[y][x] != '1')
			return (1);
	}
	return (0);
}
