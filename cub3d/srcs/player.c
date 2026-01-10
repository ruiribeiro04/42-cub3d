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

static void	ft_player_move_forward_back(t_player *player, float cos_a, float sin_a)
{
	if (player->key_up)
	{
		player->x += cos_a * MOVE_SPEED;
		player->y += sin_a * MOVE_SPEED;
	}
	if (player->key_down)
	{
		player->x -= cos_a * MOVE_SPEED;
		player->y -= sin_a * MOVE_SPEED;
	}
}

static void	ft_player_move_strafe(t_player *player, float cos_a, float sin_a)
{
	if (player->key_left)
	{
		player->x += sin_a * MOVE_SPEED;
		player->y -= cos_a * MOVE_SPEED;
	}
	if (player->key_right)
	{
		player->x -= sin_a * MOVE_SPEED;
		player->y += cos_a * MOVE_SPEED;
	}
}

void	ft_player_move_player(t_player *player)
{
	float	cos_a;
	float	sin_a;

	ft_player_rotate_player(player);
	cos_a = cosf(player->angle);
	sin_a = sinf(player->angle);
	ft_player_move_forward_back(player, cos_a, sin_a);
	ft_player_move_strafe(player, cos_a, sin_a);
}