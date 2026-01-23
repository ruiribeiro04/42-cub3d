#include "cub3d.h"

char	**realloc_map(char **map, int current_size)
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

void	strip_newline(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	line[i] = '\0';
}

char	*skip_empty_and_read(int fd)
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

int	add_line_to_map(char *line, char ***map, int *i, t_game *game)
{
	strip_newline(line);
	*map = realloc_map(*map, *i);
	if (!*map)
		return (0);
	(*map)[*i] = line;
	if ((int)ft_strlen(line) > game->map_width)
		game->map_width = ft_strlen(line);
	(*i)++;
	return (1);
}
