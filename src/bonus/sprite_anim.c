/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_anim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 16:43:20 by ruiferna          #+#    #+#             */
/*   Updated: 2026/07/17 17:16:35 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprites.h"
#include "graphics.h"

static void	compute_distances(t_game *game)
{
	t_player	*p;
	int			i;
	double		dx;
	double		dy;

	p = &game->config->player;
	i = 0;
	while (i < game->num_sprites)
	{
		dx = game->sprites[i].x - p->x;
		dy = game->sprites[i].y - p->y;
		game->sprites[i].distance = dx * dx + dy * dy;
		i++;
	}
}

static void	swap_sprites(t_sprite *a, t_sprite *b)
{
	t_sprite	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sprites_sort(t_game *game)
{
	int	i;
	int	j;
	int	max_idx;

	compute_distances(game);
	i = 0;
	while (i < game->num_sprites - 1)
	{
		max_idx = i;
		j = i + 1;
		while (j < game->num_sprites)
		{
			if (game->sprites[j].distance
				> game->sprites[max_idx].distance)
				max_idx = j;
			j++;
		}
		if (max_idx != i)
			swap_sprites(&game->sprites[i],
				&game->sprites[max_idx]);
		i++;
	}
}

void	sprites_update(t_game *game)
{
	if (!game->has_sprites || game->num_sprite_frames <= 0)
		return ;
	game->sprite_anim_counter++;
	if (game->sprite_anim_counter >= SPRITE_ANIM_DELAY)
	{
		game->sprite_anim_counter = 0;
		game->sprite_frame = (game->sprite_frame + 1)
			% game->num_sprite_frames;
	}
}
