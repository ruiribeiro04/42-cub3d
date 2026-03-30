#include "cub3d.h"

void	ft_raycasting_calc_wall_x(t_game *game)
{
	if (game->ray.side == 0)
		game->ray.wall_x = (game->player.y / BLOCK)
			+ game->ray.perp_dist * game->ray.dir_y / BLOCK;
	else
		game->ray.wall_x = (game->player.x / BLOCK)
			+ game->ray.perp_dist * game->ray.dir_x / BLOCK;
	game->ray.wall_x -= floor(game->ray.wall_x);
}

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
    t_door	*door;

    hit = 0;
    game->ray.hit_door = NULL; // Resetar a cada ray
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
        
        // Verificar se é parede normal
        if (ft_raycasting_is_wall(game, game->ray.map_x, game->ray.map_y))
            hit = 1;
        
        // Verificar se é porta
        else if (game->map[game->ray.map_y][game->ray.map_x] == 'D')
        {
            if (game->door_map) // <--- ADICIONAR ESTA SEGURANÇA
            {
                door = game->door_map[game->ray.map_y][game->ray.map_x];
                if (door && door->state != DOOR_OPEN)
                {
                    hit = 1;
                    game->ray.hit_door = door;
                }
            }
        }
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
	ft_raycasting_calc_wall_x(game);
	if (game->ray.hit_door)
    {
        int slide_pixels = (int)(game->ray.wall_height * game->ray.hit_door->progress);
        game->ray.draw_start += slide_pixels / 2;
        game->ray.draw_end -= slide_pixels / 2;
    }
}
