/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 19:03:40 by ruiferna          #+#    #+#             */
/*   Updated: 2026/07/17 17:18:01 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "player.h"
#include "raycaster.h"

int	ft_hook_key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		mlx_loop_end(game->mlx);
		return (0);
	}
	else if (keycode == KEY_W)
		game->keys.w = 1;
	else if (keycode == KEY_A)
		game->keys.a = 1;
	else if (keycode == KEY_S)
		game->keys.s = 1;
	else if (keycode == KEY_D)
		game->keys.d = 1;
	else if (keycode == KEY_LEFT)
		game->keys.left = 1;
	else if (keycode == KEY_RIGHT)
		game->keys.right = 1;
	return (0);
}

int	ft_hook_loop(t_game *game)
{
	ft_player_update(game);
	ft_raycaster_render(game);
	mlx_put_image_to_window(game->mlx, game->win,
		game->frame.ptr, 0, 0);
	return (0);
}
