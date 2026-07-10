#include "cub3d.h"

static void	ft_player_rotate_player(t_player *player)
{
	float	rot;
	float	old_dir_x;
	float	old_plane_x;

	rot = 0.0f;
	if (player->left_rotate)
		rot = -ROTATE_SPEED;
	if (player->right_rotate)
		rot = ROTATE_SPEED;
	if (rot == 0.0f)
		return ;
	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(rot) - player->dir_y * sin(rot);
	player->dir_y = old_dir_x * sin(rot) + player->dir_y * cos(rot);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(rot) - player->plane_y * sin(rot);
	player->plane_y = old_plane_x * sin(rot) + player->plane_y * cos(rot);
}

static void	ft_player_move_forward_back(t_game *game)
{
	float	new_x;
	float	new_y;

	if (game->player.key_up)
	{
		new_x = game->player.x + game->player.dir_x * MOVE_SPEED;
		new_y = game->player.y + game->player.dir_y * MOVE_SPEED;
		if (!ft_player_check_collisions(game, new_x, game->player.y))
			game->player.x = new_x;
		if (!ft_player_check_collisions(game, game->player.x, new_y))
			game->player.y = new_y;
	}
	if (game->player.key_down)
	{
		new_x = game->player.x - game->player.dir_x * MOVE_SPEED;
		new_y = game->player.y - game->player.dir_y * MOVE_SPEED;
		if (!ft_player_check_collisions(game, new_x, game->player.y))
			game->player.x = new_x;
		if (!ft_player_check_collisions(game, game->player.x, new_y))
			game->player.y = new_y;
	}
}

static void	ft_player_move_strafe(t_game *game)
{
	float	new_x;
	float	new_y;

	if (game->player.key_left)
	{
		new_x = game->player.x - game->player.plane_x * MOVE_SPEED;
		new_y = game->player.y - game->player.plane_y * MOVE_SPEED;
		if (!ft_player_check_collisions(game, new_x, game->player.y))
			game->player.x = new_x;
		if (!ft_player_check_collisions(game, game->player.x, new_y))
			game->player.y = new_y;
	}
	if (game->player.key_right)
	{
		new_x = game->player.x + game->player.plane_x * MOVE_SPEED;
		new_y = game->player.y + game->player.plane_y * MOVE_SPEED;
		if (!ft_player_check_collisions(game, new_x, game->player.y))
			game->player.x = new_x;
		if (!ft_player_check_collisions(game, game->player.x, new_y))
			game->player.y = new_y;
	}
}

void	ft_player_move(t_game *game)
{
	ft_player_rotate_player(&game->player);
	ft_player_move_forward_back(game);
	ft_player_move_strafe(game);
}
