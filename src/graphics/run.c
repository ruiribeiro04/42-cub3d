/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 13:50:06 by ruiferna          #+#    #+#             */
/*   Updated: 2026/07/17 17:20:26 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

int	ft_game_run(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, ft_hook_key_press, game);
	mlx_hook(game->win, 3, 1L << 1, ft_hook_key_release, game);
	mlx_hook(game->win, 17, 0, ft_hook_exit, game);
	mlx_loop_hook(game->mlx, ft_hook_loop, game);
	mlx_loop(game->mlx);
	return (0);
}
