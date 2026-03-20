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
	if (game->player.x >= game->map_width * BLOCK)
		return (1);
	if (game->player.y >= game->map_height * BLOCK)
		return (1);
	return (0);
}

static void	ft_raycasting_cast_ray(t_game *game, float angle, int col)
{
	ft_raycasting_init_ray(game, angle);
	ft_raycasting_calc_step(game);
	ft_raycasting_perform_dda(game);
	ft_raycasting_calc_wall_height(game, angle);
	ft_raycasting_draw_column(game, col);
}

int	ft_raycasting(t_game *game)
{
	int		col;
	float	angle;
	float	angle_step;
	float	start_angle;

	if (ft_raycasting_validate_map(game) || ft_raycasting_validate_player(game))
		return (1);
	angle_step = FOV / WIDTH;
	start_angle = game->player.angle - (FOV / 2);
	col = 0;
	while (col < WIDTH)
	{
		angle = start_angle + (col * angle_step);
		ft_raycasting_cast_ray(game, angle, col);
		col++;
	}
	return (0);
}
