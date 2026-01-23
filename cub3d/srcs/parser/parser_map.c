#include "cub3d.h"

static char	*process_first_line(char *first_line, char ***map,
	int *i, t_game *game)
{
	char	*line;

	line = first_line;
	*map = NULL;
	*i = 0;
	if (line)
	{
		strip_newline(line);
		*map = realloc_map(*map, *i);
		if (!*map)
		{
			free(line);
			return (NULL);
		}
		(*map)[*i] = line;
		if ((int)ft_strlen(line) > game->map_width)
			game->map_width = ft_strlen(line);
		(*i)++;
	}
	return (line);
}

static char	*process_map_lines(int fd, char ***map, int *i, t_game *game)
{
	char	*line;

	line = skip_empty_and_read(fd);
	while (line && line[0] != '\n')
	{
		if (!add_line_to_map(line, map, i, game))
		{
			free(line);
			return (NULL);
		}
		line = skip_empty_and_read(fd);
	}
	return (line);
}

char	**ft_parse_map_grid(int fd, t_game *game, char *first_line)
{
	char	*line;
	char	**map;
	int		i;

	if (!process_first_line(first_line, &map, &i, game))
		return (NULL);
	line = process_map_lines(fd, &map, &i, game);
	if (line)
		free(line);
	game->map_height = i;
	return (map);
}
