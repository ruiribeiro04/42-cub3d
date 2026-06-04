/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:22:47 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_sprites_render.c
 * @brief Render sprites with distance-based sorting.
 */

#include "cub3d.h"

static void	draw_stripe(t_game *g, t_sprite *sp, int stripe, t_spr_draw *d)
{
	t_texture	*tex;
	int			tex_x;
	int			y;
	int			tex_y;
	int			color;

	tex = &sp->frames[sp->current_frame];
	tex_x = (int)((stripe - d->start_x) * tex->width / d->height);
	y = d->start_y;
	while (y < d->end_y)
	{
		tex_y = (int)((y - (HEIGHT / 2 - d->height / 2)) * tex->height
				/ d->height);
		color = ft_get_texture_pixel(tex, tex_x, tex_y);
		if ((color & 0x00FFFFFF) != 0)
			ft_put_pixel_to_img(g, stripe, y, color);
		y++;
	}
}

static void	calc_draw_bounds(t_game *g, t_sprite *sp, t_spr_draw *d)
{
	double	angle;
	double	diff;
	int		screen_x;

	angle = atan2(sp->y - g->player.y, sp->x - g->player.x);
	diff = angle - g->player.angle;
	while (diff > M_PI)
		diff -= 2 * M_PI;
	while (diff < -M_PI)
		diff += 2 * M_PI;
	screen_x = (int)((0.5 + (diff / FOV)) * WIDTH);
	d->height = (int)((BLOCK / sp->distance) * (WIDTH / 2));
	d->start_y = (HEIGHT / 2) - (d->height / 2);
	d->end_y = d->start_y + d->height;
	d->start_x = screen_x - (d->height / 2);
	d->end_x = d->start_x + d->height;
	if (d->start_y < 0)
		d->start_y = 0;
	if (d->end_y > HEIGHT)
		d->end_y = HEIGHT;
	if (d->start_x < 0)
		d->start_x = 0;
	if (d->end_x > WIDTH)
		d->end_x = WIDTH;
}

static void	draw_sprite(t_game *game, t_sprite *sp)
{
	t_spr_draw	d;
	int			stripe;

	calc_draw_bounds(game, sp, &d);
	stripe = d.start_x;
	while (stripe < d.end_x)
	{
		if (sp->distance < game->z_buffer[stripe])
			draw_stripe(game, sp, stripe, &d);
		stripe++;
	}
}

/**
 * @ingroup sprites
 */
void	ft_draw_sprites(t_game *game)
{
	struct timeval	current_time;
	double			delta_time;
	int				i;

	gettimeofday(&current_time, NULL);
	delta_time = (current_time.tv_sec - game->last_time.tv_sec)
		+ (current_time.tv_usec - game->last_time.tv_usec) / 1000000.0;
	game->last_time = current_time;
	update_sprite_state(game, delta_time);
	ft_update_doors(game, delta_time);
	i = 0;
	while (i < game->sprite_count)
	{
		draw_sprite(game, &game->sprites[i]);
		i++;
	}
}
