#include "cub3d.h"

void	ft_free_doors(t_game *game)
{
	int	y;

	if (game->doors)
	{
		if (game->doors[0].tex.img && game->mlx)
			mlx_destroy_image(game->mlx, game->doors[0].tex.img);
		free(game->doors);
		game->doors = NULL;
	}
	if (game->door_map)
	{
		y = 0;
		while (y < game->map_height)
		{
			free(game->door_map[y]);
			y++;
		}
		free(game->door_map);
		game->door_map = NULL;
	}
}
