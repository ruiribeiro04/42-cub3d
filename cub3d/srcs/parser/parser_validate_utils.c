#include "cub3d.h"

int	validate_row_boundaries(t_game *game, int y, int x)
{
	int	len;

	if (y == 0 || !game->map[y + 1])
	{
		if (game->map[y][x] != '1' && game->map[y][x] != ' '
			&& game->map[y][x] != 'N' && game->map[y][x] != 'S'
			&& game->map[y][x] != 'E' && game->map[y][x] != 'W')
			return (1);
	}
	else
	{
		len = ft_strlen(game->map[y]);
		if (x == 0 || x == len - 1)
		{
			if (game->map[y][x] != '1' && game->map[y][x] != ' '
				&& game->map[y][x] != 'N' && game->map[y][x] != 'S'
				&& game->map[y][x] != 'E' && game->map[y][x] != 'W')
				return (1);
		}
	}
	return (0);
}

int	validate_space_neighbors(t_game *game, int y, int x)
{
	char	curr;

	curr = game->map[y][x];
	if (curr == ' ')
		return (0);
	if (curr == '0' || curr == 'N' || curr == 'S' || curr == 'E'
		|| curr == 'W')
	{
		if (x > 0 && game->map[y][x - 1] == ' ')
			return (1);
		if (game->map[y][x + 1] && game->map[y][x + 1] == ' ')
			return (1);
		if (y > 0 && x < (int)ft_strlen(game->map[y - 1])
			&& game->map[y - 1][x] == ' ')
			return (1);
		if (game->map[y + 1] && x < (int)ft_strlen(game->map[y + 1])
			&& game->map[y + 1][x] == ' ')
			return (1);
	}
	return (0);
}

int	validate_overhangs(t_game *game, int y, int x)
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
