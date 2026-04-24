#include "cub3d.h"

/**
* @brief Creates a copy of the map for flood-fill validation.
*
* This function creates a deep copy of the map to preserve
* the original during flood-fill marking.
*
* @param game Pointer to the game structure.
* @return char** Copy of the map, or NULL on failure.
*/
static char	**copy_map(t_game *game)
{
	char	**map_copy;
	int		y;
	int		height;

	height = 0;
	while (game->map[height])
		height++;
	map_copy = (char **)ft_calloc(height + 1, sizeof(char *));
	if (!map_copy)
		return (NULL);
	y = 0;
	while (y < height)
	{
		map_copy[y] = ft_strdup(game->map[y]);
		if (!map_copy[y])
		{
			while (y > 0)
				free(map_copy[--y]);
			free(map_copy);
			return (NULL);
		}
		y++;
	}
	map_copy[height] = NULL;
	return (map_copy);
}

/**
* @brief Recursive flood-fill algorithm to validate map closure.
*
* Starting from player position, recursively visits all reachable cells.
* Returns failure if flood-fill reaches outside map boundaries.
* Marks visited cells to prevent infinite loops.
*
* @param map_copy Copy of the map (for marking visited cells).
* @param height Map height.
* @param y Current row position.
* @param x Current column position.
* @return int 0 if map is properly closed, 1 if player can escape.
*/
static int	flood_fill(char **map_copy, int height, int y, int x)
{
	int	line_length;

	// Boundary detection: check if we've escaped the map
	if (y < 0 || y >= height)
	{
		ft_putstr_fd("Error\nMap not properly closed - boundary breach at (", 2);
		ft_putnbr_fd(y, 2);
		ft_putstr_fd(", ", 2);
		ft_putnbr_fd(x, 2);
		ft_putstr_fd(")\n", 2);
		return (1);
	}
	line_length = ft_strlen(map_copy[y]);
	if (x < 0 || x >= line_length)
	{
		ft_putstr_fd("Error\nMap not properly closed - boundary breach at (", 2);
		ft_putnbr_fd(y, 2);
		ft_putstr_fd(", ", 2);
		ft_putnbr_fd(x, 2);
		ft_putstr_fd(")\n", 2);
		return (1);
	}
	// Check if current cell is a boundary (wall, door, sprite, or space)
	if (map_copy[y][x] == '1' || map_copy[y][x] == '2'
		|| map_copy[y][x] == 'D' || map_copy[y][x] == ' ')
		return (0);
	// Check if already visited
	if (map_copy[y][x] == 'V')
		return (0);
	// Mark current cell as visited
	map_copy[y][x] = 'V';
	// Recursively visit all 4 directions
	if (flood_fill(map_copy, height, y - 1, x)) // Up
		return (1);
	if (flood_fill(map_copy, height, y + 1, x)) // Down
		return (1);
	if (flood_fill(map_copy, height, y, x - 1)) // Left
		return (1);
	if (flood_fill(map_copy, height, y, x + 1)) // Right
		return (1);
	return (0);
}

/**
* @brief Checks if a character is valid on the map.
*
* Valid characters are:
* - '0': Empty space (walkable)
* - '1': Wall
* - '2': Door/sprite (bonus feature)
* - 'D': Door (bonus feature)
* - ' ': Space (outside the playable map)
* - 'N', 'S', 'E', 'W': Player spawn positions
*
* @param c Character to check.
* @return int 1 if valid, 0 if invalid.
*/
static int	is_valid_char(char c)
{
	if (c == '0' || c == '1' || c == '2' || c == 'D' || c == ' ' || c == '\t')
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

/**
* @brief Validates all characters in the map.
*
* Traverses the entire map checking if all characters
* are valid. Prints an error message with the invalid character
* and location if found.
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
				ft_putstr_fd("Error\nInvalid character '", 2);
				ft_putchar_fd(game->map[y][x], 2);
				ft_putstr_fd("' at map position (", 2);
				ft_putnbr_fd(y, 2);
				ft_putstr_fd(", ", 2);
				ft_putnbr_fd(x, 2);
				ft_putstr_fd(")\n", 2);
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
*          due to the simple conversion with '0' + y.
*/

/**
* @brief Finds player position on the map.
*
* Scans the map to find N, S, E, or W characters.
*
* @param game Pointer to the game structure.
* @param player_y Pointer to store Y coordinate.
* @param player_x Pointer to store X coordinate.
* @return int 0 if found, 1 if not found.
*/
static int	find_player_position(t_game *game, int *player_y, int *player_x)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'N' || game->map[y][x] == 'S'
				|| game->map[y][x] == 'E' || game->map[y][x] == 'W')
			{
				*player_y = y;
				*player_x = x;
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

/**
* @brief Validates whether the map is completely closed using flood-fill.
*
* Creates a map copy and performs flood-fill from player position.
* If flood-fill reaches outside boundaries, map is invalid.
*
* @param game Pointer to the game structure.
* @return int 0 if the map is closed, 1 if there are problems.
*/
int	ft_validate_map_closed(t_game *game)
{
	char	**map_copy;
	int		result;
	int		height;
	int		player_y;
	int		player_x;

	// Find player position on map
	if (find_player_position(game, &player_y, &player_x))
	{
		ft_putstr_fd("Error\nNo player position found for flood-fill validation\n", 2);
		return (1);
	}
	// Find map height
	height = 0;
	while (game->map[height])
		height++;
	// Create a copy of the map for flood-fill
	map_copy = copy_map(game);
	if (!map_copy)
	{
		ft_putstr_fd("Error\nMemory allocation failed for map validation\n", 2);
		return (1);
	}
	// Perform flood-fill from player position
	result = flood_fill(map_copy, height, player_y, player_x);
	// Free the map copy
	height = 0;
	while (map_copy[height])
		free(map_copy[height++]);
	free(map_copy);
	return (result);
}
