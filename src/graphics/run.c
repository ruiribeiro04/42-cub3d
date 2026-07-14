/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/11 16:00:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

int	game_run(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, hook_key_press, game);
	mlx_hook(game->win, 3, 1L << 1, hook_key_release, game);
	mlx_hook(game->win, 17, 0, hook_exit, game);
	mlx_loop_hook(game->mlx, hook_loop, game);
	mlx_loop(game->mlx);
	return (0);
}
