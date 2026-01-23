#include "cub3d.h"

static int	is_valid_char(char c)
{
	if (c == '0' || c == '1' || c == ' ')
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	ft_validate_map_chars(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (!is_valid_char(game->map[y][x]))
			{
				ft_putstr_fd("Error: Invalid character '", 2);
				ft_putchar_fd(game->map[y][x], 2);
				ft_putstr_fd("' in map\n", 2);
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

static int	print_boundary_error(t_game *game, int y, int x)
{
	ft_putstr_fd("Error: Map not properly closed at row ", 2);
	ft_putchar_fd('0' + y, 2);
	ft_putstr_fd(" col ", 2);
	ft_putchar_fd('0' + x, 2);
	ft_putstr_fd(" char '", 2);
	ft_putchar_fd(game->map[y][x], 2);
	ft_putstr_fd("'\n", 2);
	return (1);
}

static int	validate_cell(t_game *game, int y, int x)
{
	if (validate_row_boundaries(game, y, x))
		return (print_boundary_error(game, y, x));
	if (validate_space_neighbors(game, y, x))
	{
		ft_putstr_fd("Error: Space adjacent to open area\n", 2);
		return (1);
	}
	if (validate_overhangs(game, y, x))
	{
		ft_putstr_fd("Error: Invalid overhang\n", 2);
		return (1);
	}
	return (0);
}

int	ft_validate_map_closed(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (validate_cell(game, y, x))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}
