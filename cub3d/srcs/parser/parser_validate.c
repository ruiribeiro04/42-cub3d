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

static int	validate_row_boundaries(t_game *game, int y, int x)
{
	int	len;

	if (y == 0 || !game->map[y + 1])
	{
		if (game->map[y][x] != '1' && game->map[y][x] != ' ' &&
			game->map[y][x] != 'N' && game->map[y][x] != 'S' &&
			game->map[y][x] != 'E' && game->map[y][x] != 'W')
			return (1);
	}
	else
	{
		len = ft_strlen(game->map[y]);
		if (x == 0 || x == len - 1)
		{
			if (game->map[y][x] != '1' && game->map[y][x] != ' ' &&
				game->map[y][x] != 'N' && game->map[y][x] != 'S' &&
				game->map[y][x] != 'E' && game->map[y][x] != 'W')
				return (1);
		}
	}
	return (0);
}

static int	validate_space_neighbors(t_game *game, int y, int x)
{
	char	curr;

	curr = game->map[y][x];
	if (curr == ' ')
		return (0);
	if (curr == '0' || curr == 'N' || curr == 'S' || curr == 'E' || curr == 'W')
	{
		if (x > 0 && game->map[y][x - 1] == ' ')
			return (1);
		if (game->map[y][x + 1] && game->map[y][x + 1] == ' ')
			return (1);
		if (y > 0 && x < (int)ft_strlen(game->map[y - 1]) &&
			game->map[y - 1][x] == ' ')
			return (1);
		if (game->map[y + 1] && x < (int)ft_strlen(game->map[y + 1]) &&
			game->map[y + 1][x] == ' ')
			return (1);
	}
	return (0);
}

static int	validate_overhangs(t_game *game, int y, int x)
{
	int	len_top;
	int	len_bottom;

	if (y > 0)
	{
		len_top = ft_strlen(game->map[y - 1]);
		if (x >= len_top && game->map[y][x] != '1')
			return (1);
	}
	if (game->map[y + 1])
	{
		len_bottom = ft_strlen(game->map[y + 1]);
		if (x >= len_bottom && game->map[y][x] != '1')
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
			if (validate_row_boundaries(game, y, x))
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
			x++;
		}
		y++;
	}
	return (0);
}
