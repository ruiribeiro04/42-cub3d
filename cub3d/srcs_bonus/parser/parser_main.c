#include "cub3d.h"

static int	ft_parse_and_validate(t_game *game, int fd, char *first_line);

/**
 * @brief Performs complete parsing of the .cub file.
 *
 * This function orchestrates the entire parsing process: it opens the file,
 * parses the configuration elements (textures and colors), and then
 * parses and validates the map.
 *
 * @param filename Path to the .cub file to be parsed.
 * @param game Pointer to the game structure where the data will be stored.
 * @return int 0 if successful, 1 if an error occurs.
 */
int	ft_parse_cub_file(char *filename, t_game *game)
{
	int		fd;
	char	*first_line;

	fd = ft_open_and_validate(filename);
	if (fd < 0)
		return (1);
	first_line = ft_parse_elements(fd, game);
	if (!first_line)
	{
		close(fd);
		return (1);
	}
	if (ft_parse_and_validate(game, fd, first_line))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

/**
 * @brief Opens and validates the .cub file.
 *
 * Checks if the file has the .cub extension and attempts to open it.
 *
 * @param filename Path to the file to be opened.
 * @return int File descriptor if successful, -1 if an error occurs.
 */
int	ft_open_and_validate(char *filename)
{
	int	len;
	int	fd;

	len = 0;
	while (filename[len])
		len++;
	if (len < 4 || ft_strncmp(&filename[len - 4], ".cub", 4))
	{
		ft_putstr_fd("Error: Invalid file extension. Must be .cub\n", 2);
		return (-1);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error: Cannot open file ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd("\n", 2);
	}
	return (fd);
}

/**
 * @brief Frees the memory allocated for texture paths.
 *
 * Frees and sets the north, south, east, and west texture paths to NULL.
 *
 * @param game Pointer to the game structure.
 */
static void	ft_free_paths(t_game *game)
{
	if (game->path_north)
		free(game->path_north);
	if (game->path_south)
		free(game->path_south);
	if (game->path_east)
		free(game->path_east);
	if (game->path_west)
		free(game->path_west);
	game->path_north = NULL;
	game->path_south = NULL;
	game->path_east = NULL;
	game->path_west = NULL;
}

/**
 * @brief Frees the memory allocated for the map.
 *
 * Frees each row of the map and then the pointer array.
 *
 * @param game Pointer to the game structure.
 */
static void	ft_free_map(t_game *game)
{
	int	i;

	if (!game->map)
		return ;
	i = 0;
	while (game->map[i])
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
	game->map = NULL;
}

/**
 * @brief Parses the map and validates it.
 *
 * This function parses the map grid, validates the characters,
 * checks if the map is closed, and initializes the player's position.
 * In case of error, it frees all allocated memory.
 *
 * @param game Pointer to the game structure.
 * @param fd File descriptor of the open file.
 * @param first_line First line of the map (already read previously).
 * @return int 0 in case of success, 1 in case of error.
 */
static int	ft_parse_and_validate(t_game *game, int fd, char *first_line)
{
	game->map = ft_parse_map_grid(fd, game, first_line);
	if (!game->map)
		return (1);
	if (ft_validate_map_chars(game) || ft_validate_map_closed(game))
	{
		ft_free_paths(game);
		ft_free_map(game);
		return (1);
	}
	// Parse door positions from map (don't load textures yet)
	if (ft_parse_doors(game) == 1)
	{
		ft_free_paths(game);
		ft_free_map(game);
		return (1);
	}
	if (ft_extract_sprites(game) == 1 || ft_init_player_from_map(game) == 1)
	{
		ft_free_doors(game);
		ft_free_parsed_sprites(game);
		ft_free_paths(game);
		ft_free_map(game);
		return (1);
	}
	return (0);
}

// void	ft_free_config(t_game *game)
// {
// 	ft_free_paths(game);
// 	ft_free_map(game);
// }
