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
	float		step;
	float		tex_pos;
	int			tex_y;
	int			color;

	tex = &sp->frames[sp->current_frame];
	tex_x = (int)((stripe - d->raw_start_x) * tex->width / d->height);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	step = (float)tex->height / d->height;
	tex_pos = (d->start_y - d->raw_start_y) * step;
	y = d->start_y;
	while (y < d->end_y)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		if (tex_y < 0)
			tex_y = 0;
		tex_pos += step;
		color = ft_get_texture_pixel(tex, tex_x, tex_y);
		if ((color & 0x00FFFFFF) != 0)
			ft_put_pixel_to_img(g, stripe, y, color);
		y++;
	}
}

static void	calc_draw_bounds(t_game *g, t_sprite *sp, t_spr_draw *d)
{
	float	spr_x;
	float	spr_y;
	float	inv_det;
	float	transform_x;
	int		screen_x;

	spr_x = sp->x - g->player.x;
	spr_y = sp->y - g->player.y;
	inv_det = 1.0f / (g->player.plane_x * g->player.dir_y
			- g->player.dir_x * g->player.plane_y);
	transform_x = inv_det * (g->player.dir_y * spr_x
			- g->player.dir_x * spr_y);
	d->transform_y = inv_det * (-g->player.plane_y * spr_x
			+ g->player.plane_x * spr_y);
	if (d->transform_y <= 0.0f)
	{
		d->start_x = -1;
		d->end_x = -1;
		return ;
	}
	screen_x = (int)((WIDTH / 2) * (1 + transform_x / d->transform_y));
	d->height = abs((int)(HEIGHT / d->transform_y));
	d->raw_start_x = -d->height / 2 + screen_x;
	d->raw_start_y = -d->height / 2 + HEIGHT / 2;
	d->start_y = d->raw_start_y;
	if (d->start_y < 0)
		d->start_y = 0;
	d->end_y = d->height / 2 + HEIGHT / 2;
	if (d->end_y > HEIGHT)
		d->end_y = HEIGHT;
	d->start_x = d->raw_start_x;
	if (d->start_x < 0)
		d->start_x = 0;
	d->end_x = d->height / 2 + screen_x;
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
		if (d.transform_y < game->z_buffer[stripe])
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
