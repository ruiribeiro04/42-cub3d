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
		game->player.angle += delta_x * MOUSE_SPEED;
		if (game->player.angle > TWO_PI)
			game->player.angle -= TWO_PI;
		else if (game->player.angle < 0)
			game->player.angle += TWO_PI;
		mlx_mouse_move(game->mlx, game->win, center_x, center_y);
	}
	(void)y;
	return (0);
}
