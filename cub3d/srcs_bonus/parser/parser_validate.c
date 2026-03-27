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
	if (c == '2')
		return (1);
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
*/
int	ft_validate_map_chars(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (!is_valid_char(game->map[y][x]))
			{
				ft_putstr_fd("Error: Invalid character '", 2);
				ft_putchar_fd(game->map[y][x], 2);
				ft_putstr_fd("' in map\n", 2);
				return (1);
			}
			x++;
		}
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
	ft_putstr_fd("Error: Map not properly closed at row ", 2);
	ft_putchar_fd('0' + y, 2);
	ft_putstr_fd(" col ", 2);
	ft_putchar_fd('0' + x, 2);
	ft_putstr_fd(" char '", 2);
	ft_putchar_fd(game->map[y][x], 2);
	ft_putstr_fd("'\n", 2);
	return (1);
}

/**
* @brief Validates an individual cell in the map.
* 
* Performs all validation checks on a specific cell:
* borders, neighbors, and overhangs.
* 
* @param game Pointer to the game structure.
* @param y Row index.
* @param x Column index.
* @return int 0 if the cell is valid, 1 if there is an error.
*/
static int	validate_cell(t_game *game, int y, int x)
{
	if (validate_row_boundaries(game, y, x))
		return (print_boundary_error(game, y, x));
	if (validate_space_neighbors(game, y, x))
	{
		ft_putstr_fd("Error: Space adjacent to open area\n", 2);
		return (1);
	}
	if (validate_overhangs(game, y, x))
	{
		ft_putstr_fd("Error: Invalid overhang\n", 2);
		return (1);
	}
	return (0);
}

/**
* @brief Validates whether the map is completely closed.
* 
* Traverses all cells in the map and checks whether the map is
* correctly closed by walls, with no holes or openings
* that would allow the player to “escape.”
* 
* @param game Pointer to the game structure.
* @return int 0 if the map is closed, 1 if there are problems.
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
			if (validate_cell(game, y, x))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}
