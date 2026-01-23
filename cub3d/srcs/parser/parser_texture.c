#include "cub3d.h"

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

static int	validate_texture_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error: Cannot open texture file: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	close(fd);
	return (0);
}

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
		ft_putstr_fd("Error: Invalid or duplicate texture\n", 2);
		return (-1);
	}
	return (1);
}
