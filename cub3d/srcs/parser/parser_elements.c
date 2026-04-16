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
* Map data consists only of: spaces, 0, 1, N, S, E, W, and tabs.
* If a line contains any other character (like letters in path names),
* it's not a map line.
*
* @param line Line to be checked.
* @return int 1 if it appears to be a map line, 0 otherwise.
*/
static int	ft_is_map_line(char *line)
{
	int		i;

	if (!line || line[0] == '\n' || line[0] == '\0')
		return (0);
	// Check if the line contains ONLY map characters
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ' && line[i] != '0' && line[i] != '1'
			&& line[i] != 'N' && line[i] != 'S' && line[i] != 'E'
			&& line[i] != 'W' && line[i] != '\t')
			return (0);  // Found a non-map character
		i++;
	}
	return (1);  // Line contains only map characters
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
