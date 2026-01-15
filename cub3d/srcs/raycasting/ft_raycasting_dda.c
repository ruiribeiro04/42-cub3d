#include "cub3d.h"

int	ft_raycasting_is_wall(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map_width)
		return (1);
	if (y < 0 || y >= game->map_height)
		return (1);
	if (game->map[y][x] == '1')
		return (1);
	return (0);
}

void	ft_raycasting_perform_dda(t_game *game)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (game->ray.side_x < game->ray.side_y)
		{
			game->ray.side_x += game->ray.delta_x;
			game->ray.map_x += game->ray.step_x;
			game->ray.side = 0;
		}
		else
		{
			game->ray.side_y += game->ray.delta_y;
			game->ray.map_y += game->ray.step_y;
			game->ray.side = 1;
		}
		if (ft_raycasting_is_wall(game, game->ray.map_x, game->ray.map_y))
			hit = 1;
	}
}

void	ft_raycasting_calc_wall_height(t_game *game, float angle)
{
	float	fish_eye;

	if (game->ray.side == 0)
		game->ray.perp_dist = game->ray.side_x - game->ray.delta_x;
	else
		game->ray.perp_dist = game->ray.side_y - game->ray.delta_y;
	game->ray.perp_dist *= BLOCK;
	fish_eye = cos(angle - game->player.angle);
	game->ray.perp_dist *= fish_eye;
	if (game->ray.perp_dist < 1.0)
		game->ray.perp_dist = 1.0;
	game->ray.wall_height = (int)((BLOCK / game->ray.perp_dist) * (WIDTH / 2));
	game->ray.draw_start = (HEIGHT - game->ray.wall_height) / 2;
	game->ray.draw_end = game->ray.draw_start + game->ray.wall_height;
}