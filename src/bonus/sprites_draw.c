/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/11 17:00:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprites.h"
#include "../graphics/graphics.h"

static int	compute_tex_x(t_sprite_draw *d, int stripe)
{
	int	base;

	base = stripe - (-d->sprite_width / 2 + d->screen_x);
	return ((int)(256 * base * TEX_SIZE / d->sprite_width / 256));
}

/* Computes tex_y from screen y using Lode's formula. */
static int	compute_tex_y(t_sprite_draw *d, int y)
{
	int	raw;

	raw = y * 256 - WIN_HEIGHT * 128 + d->sprite_height * 128;
	return (raw * TEX_SIZE / d->sprite_height / 256);
}

static void	draw_one_pixel(t_stripe_ctx *c, int y)
{
	int	tex_y;
	int	color;

	tex_y = compute_tex_y(c->d, y);
	if (tex_y < 0 || tex_y >= TEX_SIZE)
		return ;
	if (c->tex_x < 0 || c->tex_x >= TEX_SIZE)
		return ;
	color = c->g->sprite_frames[c->g->sprite_frame]
		.pixels[tex_y * TEX_SIZE + c->tex_x];
	if ((color & 0x00FFFFFF) != 0 && c->ty > 0
		&& c->ty < c->g->z_buffer[c->stripe])
		frame_put_pixel(c->g, c->stripe, y, color);
}

void	draw_sprite_stripes(t_game *g, t_sprite_draw *d, double ty)
{
	t_stripe_ctx	c;
	int				y;

	c.g = g;
	c.d = d;
	c.ty = ty;
	c.stripe = d->draw_start_x;
	while (c.stripe < d->draw_end_x)
	{
		c.tex_x = compute_tex_x(d, c.stripe);
		y = d->draw_start_y;
		while (y < d->draw_end_y)
		{
			draw_one_pixel(&c, y);
			y++;
		}
		c.stripe++;
	}
}
