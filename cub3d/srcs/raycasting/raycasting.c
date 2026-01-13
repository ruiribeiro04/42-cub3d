#include "cub3d.h"

static void	ft_raycasting_cast_ray(float *ray, float angle, t_game *game)
{
	float	cos_angle;
	float	sin_angle;

	cos_angle = cos(angle);
	sin_angle = sin(angle);
	while (ft_raycasting_touch(ray[0], ray[1], game) == 1)
	{
		ray[0] += cos_angle;
		ray[1] += sin_angle;
	}
}

static void	ft_raycasting_draw_wall_column(int x, float dist, t_game *game)
{
	float	height;
	int		start_y;
	int		end;
	int		y;

	if (dist < 1)
		dist = 1;
	height = (BLOCK / dist) * (WIDTH / 2);
	start_y = (HEIGHT - height) / 2;
	end = start_y + height;
	// Teto
	y = 0;
	while (y < start_y)
	{
		ft_put_pixel_to_img(game, x, y, 0x7F5B6F); 
		y++;
	}
	// Parede
	while (start_y < end)
	{
		if (start_y >= 0 && start_y < HEIGHT)
			ft_put_pixel_to_img(game, x, start_y, 0x4B371B);
		start_y++;
	}
	// Chao
	y = end;
	while (y < HEIGHT)
	{
		ft_put_pixel_to_img(game, x, y, 0xBF772F); 
		y++;
	}
}

void	ft_raycasting_draw_line(t_game *game, float angle, int column)
{
	float	ray[2];
	float	dist;

	ray[0] = game->player.x;
	ray[1] = game->player.y;
	ft_raycasting_cast_ray(ray, angle, game);
	dist = ft_raycasting_fixed_dist(ray[0], ray[1], game);
	ft_raycasting_draw_wall_column(column, dist, game);
}