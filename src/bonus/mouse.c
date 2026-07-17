/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-maga <vde-maga@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 17:14:22 by vde-maga          #+#    #+#             */
/*   Updated: 2026/07/17 17:14:33 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"
#include "graphics.h"
#include "player.h"
#include <math.h>

int	ft_hook_mouse_move(int x, int y, t_game *game)
{
	int	delta;

	(void)y;
	if (game->warp_skip)
	{
		game->warp_skip = 0;
		return (0);
	}
	if (!game->focused)
		return (0);
	delta = x - WIN_WIDTH / 2;
	if (delta != 0)
	{
		ft_player_rotate(&game->config->player,
			(double)delta * MOUSE_SENS);
		mlx_mouse_move(game->mlx, game->win,
			WIN_WIDTH / 2, WIN_HEIGHT / 2);
		game->warp_skip = 1;
	}
	return (0);
}
