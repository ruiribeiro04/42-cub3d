#include "cub3d.h"

/**
* @brief Checks whether a line is a configuration element line.
*
* Checks whether the line begins with a valid identifier:
* NO, SO, WE, EA (textures) or F, C (colors).
*
* @param line Line to be checked.
* @return int 1 if it is an element line, 0 otherwise.
*/
static int	ft_is_element_line(char *line)
{
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3))
		return (1);
	if (!ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		return (1);
	if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		return (1);
	return (0);
}

/**
* @brief Checks whether a line is the start of map data.
*
* Uses lenient detection: any line STARTING with '0', '1', 'N', 'S', 'E', 'W', or '2'
* is considered a map line. However, 'N', 'S', 'E', 'W' must be followed by whitespace or
* end of line to distinguish from config lines like 'NO', 'SO', etc.
*
* @param line Line to be checked.
* @return int 1 if it appears to be a map line, 0 otherwise.
*/
static int	ft_is_map_line(char *line)
{
	if (!line || line[0] == '\n' || line[0] == '\0')
		return (0);
	// Skip leading whitespace
	while (line[0] == ' ' || line[0] == '\t')
		line++;
	// Check if line starts with a wall or floor character
	if (line[0] == '0' || line[0] == '1' || line[0] == '2')
		return (1);
	// Check for player positions - must be single character followed by whitespace/end
	if (line[0] == 'N' || line[0] == 'S' || line[0] == 'E' || line[0] == 'W')
	{
		// Check if next character is whitespace, newline, or end of string
		if (line[1] == ' ' || line[1] == '\t' || line[1] == '\n' || line[1] == '\0')
			return (1);
	}
	return (0);
}

/**
* @brief Validates that all 6 required elements are present.
*
* Checks that all 4 textures and 2 colors have been set.
*
* @param game Pointer to the game structure.
* @return int 1 if all elements are present, 0 otherwise.
*/
static int	ft_has_all_required_elements(t_game *game)
{
	if (!game->path_north || !game->path_south)
		return (0);
	if (!game->path_east || !game->path_west)
		return (0);
	if (!game->floor_color_set || !game->ceiling_color_set)
		return (0);
	return (1);
}

/**
* @brief Parses an element line.
*
* Directs the line to the appropriate function (texture or color).
*
* @param line Element line to be processed.
* @param game Pointer to the game structure.
* @return int Parsing result (0 success, 1 error, -1 not processed).
*/
static int	ft_parse_element_line(char *line, t_game *game)
{
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		return (ft_parse_texture(line, game));
	else if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		return (ft_parse_color(line, game));
	return (-1);
}

/**
* @brief Skips empty lines in the file.
* 
* Reads lines until it finds one that is not empty (only newline).
* 
* @param fd File descriptor of the file.
* @return char* Pointer to the next non-empty line, or NULL if EOF.
*/
static char	*ft_skip_empty_lines(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

/**
* @brief Parses all configuration elements.
*
* Processes all configuration lines (textures and colors) until
* it finds the beginning of the map. Ignores unknown/invalid elements
* like 'R' (resolution) or 'S' (sprites). Checks if all 6 required
* elements (4 textures + 2 colors) have been defined.
*
* @param fd File descriptor of the open file.
* @param game Pointer to the game structure.
* @return char* First line of the map, or NULL in case of error.
*/
char	*ft_parse_elements(int fd, t_game *game)
{
	char	*line;
	int		count;
	int		ret;

	line = ft_skip_empty_lines(fd);
	count = 0;
	while (line && !ft_is_map_line(line))
	{
		if (ft_is_element_line(line))
		{
			ret = ft_parse_element_line(line, game);
			if (ret == 1)
			{
				free(line);
				ft_putstr_fd("Error: Invalid or duplicate config elements\n", 2);
				return (NULL);
			}
			if (ret == 0)
				count++;
		}
		// Unknown/invalid lines are silently ignored
		free(line);
		line = ft_skip_empty_lines(fd);
	}
	if (!ft_has_all_required_elements(game))
	{
		if (line)
			free(line);
		ft_putstr_fd("Error: Missing required config elements (NO, SO, WE, EA, F, C)\n", 2);
		return (NULL);
	}
	return (line);
}
