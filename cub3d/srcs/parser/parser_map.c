#include "cub3d.h"

static char	**realloc_map(char **map, int current_size)
{
	char	**new_map;
	int		i;

	new_map = (char **)malloc(sizeof(char *) * (current_size + 2));
	if (!new_map)
		return (NULL);
	i = 0;
	while (i < current_size)
	{
		new_map[i] = map[i];
		i++;
	}
	new_map[current_size + 1] = NULL;
	if (map)
		free(map);
	return (new_map);
}

static void	strip_newline(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	line[i] = '\0';
}

char	**ft_parse_map_grid(int fd, t_game *game)
{
	char	*line;
	char	**map;
	int		i;

	// Get the first map line that was saved by ft_parse_elements
	line = get_first_map_line();
	map = NULL;
	i = 0;
	if (line)
	{
		strip_newline(line);
		map = realloc_map(map, i);
		if (!map)
		{
			free(line);
			return (NULL);
		}
		map[i] = line;
		if ((int)ft_strlen(line) > game->map_width)
			game->map_width = ft_strlen(line);
		i++;
	}
	// Continue reading the rest of the map
	line = get_next_line(fd);
	while (line && line[0] == '\n')
		line = get_next_line(fd);
	while (line && line[0] != '\n')
	{
		strip_newline(line);
		map = realloc_map(map, i);
		if (!map)
		{
			free(line);
			return (NULL);
		}
		map[i] = line;
		if ((int)ft_strlen(line) > game->map_width)
			game->map_width = ft_strlen(line);
		i++;
		line = get_next_line(fd);
		while (line && line[0] == '\n')
			line = get_next_line(fd);
	}
	if (line)
		free(line);
	game->map_height = i;
	return (map);
}
