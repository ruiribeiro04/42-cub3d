#include "cub3d.h"

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

static int	ft_parse_element_line(char *line, t_game *game)
{
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		return (ft_parse_texture(line, game));
	else if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		return (ft_parse_color(line, game));
	return (0);
}

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
