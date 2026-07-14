/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/11 16:00:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"
#include "../bonus/bonus.h"

int	game_run(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, hook_key_press, game);
	mlx_hook(game->win, 3, 1L << 1, hook_key_release, game);
	mlx_hook(game->win, 17, 0, hook_exit, game);
	mlx_hook(game->win, 6, 1L << 6, hook_mouse_move, game);
	mlx_hook(game->win, 9, 1L << 21, hook_focus_in, game);
	mlx_hook(game->win, 10, 1L << 21, hook_focus_out, game);
	mlx_mouse_move(game->mlx, game->win,
		WIN_WIDTH / 2, WIN_HEIGHT / 2);
	mlx_loop_hook(game->mlx, hook_loop, game);
	mlx_loop(game->mlx);
	return (0);
}
