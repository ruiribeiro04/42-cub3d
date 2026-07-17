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
#include "graphics.h"
#include <math.h>

void	ft_player_update(t_game *game)
{
	t_player	*p;
	t_keys		*k;

	p = &game->config->player;
	k = &game->keys;
	ft_apply_movement(game, p, k);
	if (k->left)
		ft_player_rotate(p, -ROT_SPEED);
	if (k->right)
		ft_player_rotate(p, ROT_SPEED);
}
