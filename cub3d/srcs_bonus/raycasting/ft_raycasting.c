#include "cub3d.h"

static int	ft_raycasting_validate_map(t_game *game)
{
	if (!game->map)
		return (1);
	if (game->map_width <= 0 || game->map_height <= 0)
		return (1);
	return (0);
}

static int	ft_raycasting_validate_player(t_game *game)
{
	if (game->player.x < 0 || game->player.y < 0)
		return (1);
	if (game->player.x >= (float)game->map_width)
		return (1);
	if (game->player.y >= (float)game->map_height)
		return (1);
	return (0);
}

static void	ft_raycasting_cast_ray(t_game *game, float ray_dir_x,
			float ray_dir_y, int col)
{
	ft_raycasting_init_ray(game, ray_dir_x, ray_dir_y);
	ft_raycasting_calc_step(game);
	ft_raycasting_perform_dda(game);
	ft_raycasting_calc_wall_height(game);
	ft_raycasting_draw_column(game, col);
}

int	ft_raycasting(t_game *game)
{
	int		col;
	float	camera_x;
	float	ray_dir_x;
	float	ray_dir_y;

	if (ft_raycasting_validate_map(game) || ft_raycasting_validate_player(game))
		return (1);
	col = 0;
	while (col < WIDTH)
	{
		camera_x = 2.0f * col / (float)WIDTH - 1.0f;
		ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
		ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
		ft_raycasting_cast_ray(game, ray_dir_x, ray_dir_y, col);
		game->z_buffer[col] = game->ray.perp_dist;
		col++;
	}
	ft_draw_sprites(game);
	ft_draw_minimap(game);
	return (0);
}
