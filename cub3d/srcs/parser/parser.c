#include "../includes/cub3d.h"

// TODO: Need to implement the logic here

// char	**parse_map(char *filename, t_game *game)
// {
// 	int		fd;
// 	char	**map;
// 	int		i;

// 	fd = open(filename, O_RDONLY);
// 	if (fd < 0)
// 		return (NULL);
// 	game->map_height = count_valid_lines(filename);
// 	if (game->map_height == 0)
// 		return (close(fd), NULL);
// 	map = malloc(sizeof(char *) * (game->map_height + 1));
// 	if (!map)
// 		return (close(fd), NULL);
// 	i = 0;
// 	if (!parse_map_lines(fd, map, &i, game))
// 	{
// 		close(fd);
// 		free_map_partial(map, i);
// 		return (NULL);
// 	}
// 	map[i] = NULL;
// 	close(fd);
// 	return (map);
// }

// static int	cleanup_and_fail(int fd, char *line_to_free)
// {
// 	char	*discard;

// 	if (line_to_free)
// 		free(line_to_free);
// 	discard = get_next_line(fd);
// 	while (discard)
// 	{
// 		free(discard);
// 		discard = get_next_line(fd);
// 	}
// 	return (0);
// }

// int	parse_map_lines(int fd, char **map, int *i, t_game *game)
// {
// 	char	*line;
// 	char	*temp;

// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		if (line[0] == '\n' || is_empty_line(line))
// 			return (cleanup_and_fail(fd, line));
// 		temp = ft_strtrim(line, "\n");
// 		if (!temp || temp[0] == '\0')
// 		{
// 			free(temp);
// 			return (cleanup_and_fail(fd, line));
// 		}
// 		free(line);
// 		line = temp;
// 		map[*i] = line;
// 		if (*i == 0)
// 			game->map_width = ft_strlen(line);
// 		else if ((int)ft_strlen(line) != game->map_width)
// 			return (cleanup_and_fail(fd, line));
// 		(*i)++;
// 		line = get_next_line(fd);
// 	}
// 	return (1);
// }

