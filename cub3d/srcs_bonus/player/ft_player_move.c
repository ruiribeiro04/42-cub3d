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
