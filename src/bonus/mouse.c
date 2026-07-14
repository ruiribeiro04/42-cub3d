/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   mouse.c						:+:	 :+:	:+:   */
/*						      +:+ +:+	      +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+	 +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2025/07/10 19:00:00 by ruiferna	       #+#    #+#	      */
/*   Updated: 2025/07/11 16:00:00 by ruiferna	      ###   ########.fr	      */
/*									      */
/* ************************************************************************** */
#include "bonus.h"
#include "graphics.h"
#include "player.h"
#include <math.h>

int	hook_mouse_move(int x, int y, t_game *game)
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
		player_rotate(&game->config->player,
			(double)delta * MOUSE_SENS);
		mlx_mouse_move(game->mlx, game->win,
			WIN_WIDTH / 2, WIN_HEIGHT / 2);
		game->warp_skip = 1;
	}
	return (0);
}
