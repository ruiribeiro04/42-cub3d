/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/11 16:00:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "sprites.h"
#include "../graphics/graphics.h"
#include <math.h>
#include <stdlib.h>

static void	compute_transform(t_player *p, t_sprite *s,
								double *tx, double *ty)
{
	double	sx;
	double	sy;
	double	inv_det;
	double	det;

	sx = s->x - p->x;
	sy = s->y - p->y;
	det = p->plane_x * p->dir_y - p->dir_x * p->plane_y;
	if (det == 0)
		inv_det = 1e30;
	else
		inv_det = 1.0 / det;
	*tx = inv_det * (p->dir_y * sx - p->dir_x * sy);
	*ty = inv_det * (-p->plane_y * sx + p->plane_x * sy);
}

static void	compute_draw(t_sprite_draw *d, int screen_x, double ty)
{
	d->screen_x = screen_x;
	d->sprite_height = abs((int)(WIN_HEIGHT / ty));
	d->sprite_width = d->sprite_height;
	d->draw_start_y = -d->sprite_height / 2 + WIN_HEIGHT / 2;
	if (d->draw_start_y < 0)
		d->draw_start_y = 0;
	d->draw_end_y = d->sprite_height / 2 + WIN_HEIGHT / 2;
	if (d->draw_end_y >= WIN_HEIGHT)
		d->draw_end_y = WIN_HEIGHT - 1;
	d->draw_start_x = -d->sprite_width / 2 + screen_x;
	if (d->draw_start_x < 0)
		d->draw_start_x = 0;
	d->draw_end_x = d->sprite_width / 2 + screen_x;
	if (d->draw_end_x >= WIN_WIDTH)
		d->draw_end_x = WIN_WIDTH - 1;
}

void	render_one_sprite(t_game *g, t_sprite *s)
{
	t_sprite_draw	d;
	double			tx;
	double			ty;
	int				screen_x;

	compute_transform(&g->config->player, s, &tx, &ty);
	if (ty <= 0)
		return ;
	screen_x = (int)((WIN_WIDTH / 2) * (1.0 + tx / ty));
	compute_draw(&d, screen_x, ty);
	draw_sprite_stripes(g, &d, ty);
}

void	sprites_render(t_game *game)
{
	int	i;

	if (!game->has_sprites)
		return ;
	sprites_sort(game);
	i = 0;
	while (i < game->num_sprites)
	{
		render_one_sprite(game, &game->sprites[i]);
		i++;
	}
}
