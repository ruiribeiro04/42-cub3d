#include "cub3d.h"

void	ft_init_player_from_map(t_game *game)
{
	int	y;
	int	x;
	int	spawn_count;
	int	spawn_x;
	int	spawn_y;

	spawn_count = 0;
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'N' || game->map[y][x] == 'S' ||
				game->map[y][x] == 'E' || game->map[y][x] == 'W')
			{
				spawn_x = x;
				spawn_y = y;
				spawn_count++;
				if (game->map[y][x] == 'N')
					game->player.angle = 3 * PI / 2;
				else if (game->map[y][x] == 'S')
					game->player.angle = PI / 2;
				else if (game->map[y][x] == 'E')
					game->player.angle = 0;
				else if (game->map[y][x] == 'W')
					game->player.angle = PI;
				game->map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	if (spawn_count == 0)
	{
		ft_putstr_fd("Error: No player spawn position found\n", 2);
		return ;
	}
	if (spawn_count > 1)
	{
		ft_putstr_fd("Error: Multiple player spawn positions found\n", 2);
		return ;
	}
	game->player.x = (spawn_x + 0.5) * BLOCK;
	game->player.y = (spawn_y + 0.5) * BLOCK;
}
