#include "cub3d.h"

static char	*g_first_map_line = NULL;

static int	is_element_line(char *line)
{
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3))
		return (1);
	if (!ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		return (1);
	if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		return (1);
	return (0);
}

char	*get_first_map_line(void)
{
	return (g_first_map_line);
}

int	ft_parse_elements(int fd, t_game *game)
{
	char	*line;
	int		count;

	line = get_next_line(fd);
	while (line && line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	count = 0;
	while (line && is_element_line(line))
	{
		if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3) ||
			!ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
			count += ft_parse_texture(line, game);
		else if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
			count += ft_parse_color(line, game);
		free(line);
		line = get_next_line(fd);
		while (line && line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
		}
	}
	// At this point, line is either:
	// 1. NULL (EOF) - error
	// 2. A newline - skip it
	// 3. The first map line - save it!
	while (line && line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	if (line && !is_element_line(line))
	{
		// This is the first map line - save it for ft_parse_map_grid
		g_first_map_line = line;
	}
	if (count != 6)
		return (ft_putstr_fd("Error: Missing or duplicate config elements\n", 2), 1);
	return (0);
}
