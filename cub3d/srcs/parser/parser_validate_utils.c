#include "cub3d.h"

/**
* @brief Validates the boundaries of a row in the map.
* 
* Checks whether the cells at the edges (first/last row or
* first/last column) contain only valid boundary characters
* (‘1’, ‘ ’, ‘N’, ‘S’, ‘E’, ‘W’).
* 
* @param game Pointer to the game structure.
* @param y Index of the row to check.
* @param x Index of the column to check.
* @return int 0 if valid, 1 if invalid.
*/
int	validate_row_boundaries(t_game *game, int y, int x)
{
	int	len;

	if (y == 0 || !game->map[y + 1])
	{
		if (game->map[y][x] != '1' && game->map[y][x] != ' '
			&& game->map[y][x] != 'N' && game->map[y][x] != 'S'
			&& game->map[y][x] != 'E' && game->map[y][x] != 'W')
			return (1);
	}
	else
	{
		len = ft_strlen(game->map[y]);
		if (x == 0 || x == len - 1)
		{
			if (game->map[y][x] != '1' && game->map[y][x] != ' '
				&& game->map[y][x] != 'N' && game->map[y][x] != 'S'
				&& game->map[y][x] != 'E' && game->map[y][x] != 'W')
				return (1);
		}
	}
	return (0);
}

/**
* @brief Validates whether walkable cells are not adjacent to spaces.
* 
* Checks whether cells with ‘0’ or spawn (N, S, E, W) do not have
* empty spaces (‘ ’) as direct neighbors (up, down, left, right).
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
	if (curr == '0' || curr == 'N' || curr == 'S' || curr == 'E'
		|| curr == 'W')
	{
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
	}
	return (0);
}

/**
* @brief Validates overhangs on the map.
* 
* Checks for cells that extend beyond adjacent lines
* without being walls (‘1’). This prevents maps with invalid shapes
* where walkable areas are exposed to the “void.”
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
	return (0);
}
