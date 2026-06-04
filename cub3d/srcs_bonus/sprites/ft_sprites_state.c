/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites_state.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:22:51 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_sprites_state.c
 * @brief Manage sprite animation state.
 */

#include "cub3d.h"

static void	update_animation(t_sprite *sp, double delta_time)
{
	sp->anim_time += delta_time;
	if (sp->anim_time >= 0.2)
	{
		sp->anim_time = 0;
		sp->current_frame++;
		if (sp->current_frame >= sp->frame_count)
			sp->current_frame = 0;
	}
}

static void	calc_dist_and_anim(t_game *game, double delta_time)
{
	t_sprite	*sp;
	double		dx;
	double		dy;
	int			i;

	i = 0;
	while (i < game->sprite_count)
	{
		sp = &game->sprites[i];
		update_animation(sp, delta_time);
		dx = sp->x - game->player.x;
		dy = sp->y - game->player.y;
		sp->distance = sqrt(dx * dx + dy * dy);
		i++;
	}
}

static void	sort_sprites(t_game *game)
{
	t_sprite	tmp;
	int			i;
	int			j;

	i = 0;
	while (i < game->sprite_count - 1)
	{
		j = 0;
		while (j < game->sprite_count - i - 1)
		{
			if (game->sprites[j].distance < game->sprites[j + 1].distance)
			{
				tmp = game->sprites[j];
				game->sprites[j] = game->sprites[j + 1];
				game->sprites[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	update_sprite_state(t_game *game, double delta_time)
{
	calc_dist_and_anim(game, delta_time);
	sort_sprites(game);
}
