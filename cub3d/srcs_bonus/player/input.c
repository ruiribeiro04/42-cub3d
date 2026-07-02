#include "cub3d.h"

int	ft_input_key_press(int keycode, t_game *game)
{
	if (keycode == W)
		game->player.key_up = true;
	if (keycode == S)
		game->player.key_down = true;
	if (keycode == A)
		game->player.key_left = true;
	if (keycode == D)
		game->player.key_right = true;
	if (keycode == LEFT)
		game->player.left_rotate = true;
	if (keycode == RIGHT)
		game->player.right_rotate = true;
	if (keycode == E)
		ft_handle_door_interaction(game);
	if (keycode == ESC || keycode == Q)
		ft_exit_game(game);
	return (0);
}

int	ft_input_key_release(int keycode, t_game *game)
{
	if (keycode == W)
		game->player.key_up = false;
	if (keycode == S)
		game->player.key_down = false;
	if (keycode == A)
		game->player.key_left = false;
	if (keycode == D)
		game->player.key_right = false;
	if (keycode == LEFT)
		game->player.left_rotate = false;
	if (keycode == RIGHT)
		game->player.right_rotate = false;
	return (0);
}

int	ft_input_mouse_move(int x, int y, t_game *game)
{
	int			center_x;
	int			center_y;
	int			delta_x;
	static int	first_call = 1;

	center_x = WIDTH / 2;
	center_y = HEIGHT / 2;
	if (first_call)
	{
		mlx_mouse_move(game->mlx, game->win, center_x, center_y);
		first_call = 0;
		return (0);
	}
	delta_x = x - center_x;
	if (delta_x != 0)
	{
		float	rot;
		float	old_dir_x;
		float	old_plane_x;

		rot = delta_x * MOUSE_SPEED;
		old_dir_x = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(rot)
			- game->player.dir_y * sin(rot);
		game->player.dir_y = old_dir_x * sin(rot)
			+ game->player.dir_y * cos(rot);
		old_plane_x = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(rot)
			- game->player.plane_y * sin(rot);
		game->player.plane_y = old_plane_x * sin(rot)
			+ game->player.plane_y * cos(rot);
		mlx_mouse_move(game->mlx, game->win, center_x, center_y);
	}
	(void)y;
	return (0);
}
