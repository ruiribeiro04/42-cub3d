#include "cub3d.h"

float	ft_raycasting_distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	ft_raycasting_fixed_dist(float x2, float y2, t_game *game)
{
	float	delta_x;
	float	delta_y;
	float	angle;

	delta_x = x2 - game->player.x;
	delta_y = y2 - game->player.y;
	angle = atan2(delta_y, delta_x) - game->player.angle;
	return (ft_raycasting_distance(delta_x, delta_y) * cos(angle));
}

int	ft_raycasting_touch(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (y < 0 || y >= 10 || x < 0 || x >= 15)
		return (0);
	if (game->map[y][x] == '1')
		return (0);
	return (1);
}