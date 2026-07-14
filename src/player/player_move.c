/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/11 16:00:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "player.h"
#include "../graphics/graphics.h"
#include <math.h>

static void	player_rotate(t_player *p, double rot)
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

void	player_update(t_game *game)
{
	t_player	*p;
	t_keys		*k;

	p = &game->config->player;
	k = &game->keys;
	apply_movement(game, p, k);
	if (k->left)
		player_rotate(p, -ROT_SPEED);
	if (k->right)
		player_rotate(p, ROT_SPEED);
}
