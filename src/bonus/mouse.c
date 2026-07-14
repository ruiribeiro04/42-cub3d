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
#include <math.h>

static void	rotate_player(t_player *p, double rot)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos(rot) - p->dir_y * sin(rot);
	p->dir_y = old_dir_x * sin(rot) + p->dir_y * cos(rot);
	old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos(rot) - p->plane_y * sin(rot);
	p->plane_y = old_plane_x * sin(rot) + p->plane_y * cos(rot);
}

int	hook_mouse_move(int x, int y, t_game *game)
{
	int	delta;

	(void)y;
	delta = x - WIN_WIDTH / 2;
	if (delta != 0)
	{
		rotate_player(&game->config->player,
			(double)delta * MOUSE_SENS);
		mlx_mouse_move(game->mlx, game->win,
			WIN_WIDTH / 2, WIN_HEIGHT / 2);
	}
	return (0);
}
