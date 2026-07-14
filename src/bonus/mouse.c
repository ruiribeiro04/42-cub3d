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
#include "../graphics/graphics.h"
#include "../player/player.h"
#include <math.h>

int	hook_mouse_move(int x, int y, t_game *game)
{
	int	delta;

	(void)y;
	delta = x - WIN_WIDTH / 2;
	if (delta != 0)
	{
		player_rotate(&game->config->player,
			(double)delta * MOUSE_SENS);
		mlx_mouse_move(game->mlx, game->win,
			WIN_WIDTH / 2, WIN_HEIGHT / 2);
	}
	return (0);
}
