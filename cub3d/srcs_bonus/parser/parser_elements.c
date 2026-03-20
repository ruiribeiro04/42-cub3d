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
* @brief Parses an element line.
* 
* Directs the line to the appropriate function (texture or color).
* 
* @param line Element line to be processed.
* @param game Pointer to the game structure.
* @return int Parsing result (1 success, -1 error, 0 not processed).
*/
static int	ft_parse_element_line(char *line, t_game *game)
{
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		return (ft_parse_texture(line, game));
	else if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		return (ft_parse_color(line, game));
	return (0);
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
* it finds the beginning of the map. Checks if all 6 elements
* (4 textures + 2 colors) have been defined.
* 
* @param fd File descriptor of the open file.
* @param game Pointer to the game structure.
* @return char* First line of the map, or NULL in case of error.
*/
char	*ft_parse_elements(int fd, t_game *game)
{
	char	*line;
	int		count;

	line = ft_skip_empty_lines(fd);
	count = 0;
	while (line && ft_is_element_line(line))
	{
		count += ft_parse_element_line(line, game);
		free(line);
		line = ft_skip_empty_lines(fd);
	}
	if (count != 6)
	{
		if (line)
			free(line);
		ft_putstr_fd("Error: Missing or duplicate config elements\n", 2);
		return (NULL);
	}
	return (line);
}
