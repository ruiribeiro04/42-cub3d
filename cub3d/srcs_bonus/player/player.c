#include "cub3d.h"

static void	ft_player_rotate_player(t_player *player)
{
	if (player->left_rotate)
		player->angle -= ROTATE_SPEED;
	if (player->right_rotate)
		player->angle += ROTATE_SPEED;
	if (player->angle > TWO_PI)
		player->angle = 0;
	else if (player->angle < 0)
		player->angle = TWO_PI;
}

static int	ft_player_check_collision(t_game *game, float x, float y)
{
    int	map_x;
    int	map_y;
    int	i;
    int	j;
    t_door	*door;

	if (!game->door_map) // <--- ADICIONAR ESTA LINHA DE SEGURANÇA
        return (0);       // Se não há portas, não há colisão de portas
    i = -1;
    while (i <= 1)
    {
        j = -1;
        while (j <= 1)
        {
            map_x = (int)((x + i * COLLISION_MARGIN) / BLOCK);
            map_y = (int)((y + j * COLLISION_MARGIN) / BLOCK);
            if (map_x < 0 || map_x >= game->map_width)
                return (1);
            if (map_y < 0 || map_y >= game->map_height)
                return (1);
            if (game->map[map_y][map_x] == '1')
                return (1);
            // NOVO: Colisão com portas
            if (game->map[map_y][map_x] == 'D')
            {
                door = game->door_map[map_y][map_x];
                if (door && door->state != DOOR_OPEN)
                    return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}

static void	ft_player_move_forward_back(t_game *game, float cos_a, float sin_a)
{
	float	new_x;
	float	new_y;

	if (game->player.key_up)
	{
		new_x = game->player.x + cos_a * MOVE_SPEED;
		new_y = game->player.y + sin_a * MOVE_SPEED;
		if (!ft_player_check_collision(game, new_x, game->player.y))
			game->player.x = new_x;
		if (!ft_player_check_collision(game, game->player.x, new_y))
			game->player.y = new_y;
	}
	if (game->player.key_down)
	{
		new_x = game->player.x - cos_a * MOVE_SPEED;
		new_y = game->player.y - sin_a * MOVE_SPEED;
		if (!ft_player_check_collision(game, new_x, game->player.y))
			game->player.x = new_x;
		if (!ft_player_check_collision(game, game->player.x, new_y))
			game->player.y = new_y;
	}
}

static void	ft_player_move_strafe(t_game *game, float cos_a, float sin_a)
{
	float	new_x;
	float	new_y;

	if (game->player.key_left)
	{
		new_x = game->player.x + sin_a * MOVE_SPEED;
		new_y = game->player.y - cos_a * MOVE_SPEED;
		if (!ft_player_check_collision(game, new_x, game->player.y))
			game->player.x = new_x;
		if (!ft_player_check_collision(game, game->player.x, new_y))
			game->player.y = new_y;
	}
	if (game->player.key_right)
	{
		new_x = game->player.x - sin_a * MOVE_SPEED;
		new_y = game->player.y + cos_a * MOVE_SPEED;
		if (!ft_player_check_collision(game, new_x, game->player.y))
			game->player.x = new_x;
		if (!ft_player_check_collision(game, game->player.x, new_y))
			game->player.y = new_y;
	}
}

void	ft_player_move(t_game *game)
{
	float	cos_a;
	float	sin_a;

	ft_player_rotate_player(&game->player);
	cos_a = cos(game->player.angle);
	sin_a = sin(game->player.angle);
	ft_player_move_forward_back(game, cos_a, sin_a);
	ft_player_move_strafe(game, cos_a, sin_a);
}
