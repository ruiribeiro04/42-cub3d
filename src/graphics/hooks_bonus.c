/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   hooks_bonus.c					:+:	 :+:	:+:   */
/*						      +:+ +:+	      +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+	 +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2025/07/10 19:00:00 by ruiferna	       #+#    #+#	      */
/*   Updated: 2025/07/11 16:00:00 by ruiferna	      ###   ########.fr	      */
/*									      */
/* ************************************************************************** */
#include "graphics.h"
#include "bonus.h"
#include "sprites.h"

int	hook_key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		mlx_loop_end(game->mlx);
		return (0);
	}
	if (keycode == KEY_W)
		game->keys.w = 1;
	if (keycode == KEY_A)
		game->keys.a = 1;
	if (keycode == KEY_S)
		game->keys.s = 1;
	if (keycode == KEY_D)
		game->keys.d = 1;
	if (keycode == KEY_LEFT)
		game->keys.left = 1;
	if (keycode == KEY_RIGHT)
		game->keys.right = 1;
	if (keycode == KEY_E)
		door_try_front(game);
	return (0);
}

int	hook_focus_in(t_game *game)
{
	game->focused = 1;
	mlx_mouse_move(game->mlx, game->win,
		WIN_WIDTH / 2, WIN_HEIGHT / 2);
	return (0);
}

int	hook_focus_out(t_game *game)
{
	game->focused = 0;
	return (0);
}

int	hook_loop(t_game *game)
{
	player_update(game);
	raycaster_render(game);
	sprites_update(game);
	sprites_render(game);
	minimap_draw(game);
	mlx_put_image_to_window(game->mlx, game->win,
		game->frame.ptr, 0, 0);
	return (0);
}
