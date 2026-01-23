#include "cub3d.h"

static void	ft_free_split(char **values)
{
	int	i;

	i = 0;
	while (values[i])
	{
		free(values[i]);
		i++;
	}
	free(values);
}

static int	ft_parse_rgb_values(char *line, int *r, int *g, int *b)
{
	char	**values;
	int		result;

	values = ft_split(&line[2], ' ');
	if (!values)
		return (1);
	result = 0;
	if (!values[0] || !values[1] || !values[2] || values[3])
		result = 1;
	if (!result)
	{
		*r = ft_atoi(values[0]);
		*g = ft_atoi(values[1]);
		*b = ft_atoi(values[2]);
		if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
			result = 1;
	}
	ft_free_split(values);
	return (result);
}

int	ft_parse_color(char *line, t_game *game)
{
	int	r;
	int	g;
	int	b;
	int	color;

	if (ft_parse_rgb_values(line, &r, &g, &b))
		return (ft_putstr_fd("Error: Invalid RGB color format\n", 2), -1);
	color = (r << 16) | (g << 8) | b;
	if (!ft_strncmp(line, "F ", 2))
	{
		if (game->floor_color != 0)
			return (ft_putstr_fd("Error: Duplicate floor color\n", 2), -1);
		game->floor_color = color;
	}
	else if (!ft_strncmp(line, "C ", 2))
	{
		if (game->ceiling_color != 0)
			return (ft_putstr_fd("Error: Duplicate ceiling color\n", 2), -1);
		game->ceiling_color = color;
	}
	return (1);
}
