#include "cub3d.h"

/**
* @brief Extracts the texture path from a configuration line.
* 
* Skips spaces after the identifier and copies the path,
* removing the newline character if it exists.
* 
* @param line Complete configuration line.
* @param start Starting position to begin searching for the path.
* @return char* Extracted path (allocated), or NULL in case of error.
*/
static char	*extract_path(char *line, int start)
{
	int		i;
	char	*path;

	i = start;
	while (line[i] && line[i] == ' ')
		i++;
	path = ft_strdup(&line[i]);
	if (!path)
		return (NULL);
	i = 0;
	while (path[i] && path[i] != '\n')
		i++;
	path[i] = '\0';
	return (path);
}

/**
* @brief Validates whether the texture file exists and can be opened.
* 
* Attempts to open the file in read mode to verify its existence.
* 
* @param path Path to the texture file.
* @return int 0 if valid, 1 if unable to open the file.
*/
int	validate_texture_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nCannot open texture file: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	close(fd);
	return (0);
}

/**
* @brief Parses North and South textures.
* 
* Processes lines beginning with “NO ” or “SO ”, extracts the path,
* validates it, and stores it in the game structure. Checks for duplicates.
* 
* @param line Configuration line.
* @param game Pointer to the game structure.
* @param path Pointer to store the extracted path.
* @return int 0 on success, 1 on error.
*/
static int	parse_north_south(char *line, t_game *game, char **path)
{
	if (!ft_strncmp(line, "NO ", 3))
	{
		*path = extract_path(line, 3);
		if (*path && !validate_texture_path(*path) && !game->path_north)
			game->path_north = *path;
		else
			return (1);
	}
	else if (!ft_strncmp(line, "SO ", 3))
	{
		*path = extract_path(line, 3);
		if (*path && !validate_texture_path(*path) && !game->path_south)
			game->path_south = *path;
		else
			return (1);
	}
	return (0);
}

/**
* @brief Parses West and East textures.
* 
* Processes lines beginning with “WE ” or “EA ”, extracts the path,
* validates it, and stores it in the game structure. Checks for duplicates.
* 
* @param line Configuration line.
* @param game Pointer to the game structure.
* @param path Pointer to store the extracted path.
* @return int 0 on success, 1 on error.
*/
static int	parse_west_east(char *line, t_game *game, char **path)
{
	if (!ft_strncmp(line, "WE ", 3))
	{
		*path = extract_path(line, 3);
		if (*path && !validate_texture_path(*path) && !game->path_west)
			game->path_west = *path;
		else
			return (1);
	}
	else if (!ft_strncmp(line, "EA ", 3))
	{
		*path = extract_path(line, 3);
		if (*path && !validate_texture_path(*path) && !game->path_east)
			game->path_east = *path;
		else
			return (1);
	}
	return (0);
}

/**
* @brief Parses a texture line.
* 
* Main function that coordinates the parsing of any texture line,
* delegating to the specific functions for each direction.
* 
* @param line Texture configuration line.
* @param game Pointer to the game structure.
* @return int 1 on success, -1 on error.
*/
int	ft_parse_texture(char *line, t_game *game)
{
	char	*path;
	int		result;

	result = 0;
	path = NULL;
	result = parse_north_south(line, game, &path);
	if (!result)
		result = parse_west_east(line, game, &path);
	if (result)
	{
		if (path)
			free(path);
		ft_putstr_fd("Error\nInvalid or duplicate texture\n", 2);
		return (-1);
	}
	return (1);
}
