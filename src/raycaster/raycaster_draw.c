/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   raycaster_draw.c					:+:	 :+:	:+:   */
/*						      +:+ +:+	      +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+	 +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2025/07/10 19:00:00 by ruiferna	       #+#    #+#	      */
/*   Updated: 2025/07/11 16:00:00 by ruiferna	      ###   ########.fr	      */
/*									      */
/* ************************************************************************** */
#include "raycaster.h"
#include "graphics.h"
#include <math.h>

static void	compute_height(t_ray *r)
{
	if (r->perp_wall_dist < 1e-6)
		r->perp_wall_dist = 1e-6;
	r->line_height = (int)(WIN_HEIGHT / r->perp_wall_dist);
	r->draw_start = -r->line_height / 2 + WIN_HEIGHT / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + WIN_HEIGHT / 2;
	if (r->draw_end >= WIN_HEIGHT)
		r->draw_end = WIN_HEIGHT - 1;
}

static void	compute_texture(t_ray *r, t_player *p)
{
	if (r->side == 0)
	{
		if (r->dir_x > 0)
			r->tex_num = TEX_EAST;
		else
			r->tex_num = TEX_WEST;
		r->wall_x = p->y + r->perp_wall_dist * r->dir_y;
	}
	else
	{
		if (r->dir_y > 0)
			r->tex_num = TEX_SOUTH;
		else
			r->tex_num = TEX_NORTH;
		r->wall_x = p->x + r->perp_wall_dist * r->dir_x;
	}
	r->wall_x -= floor(r->wall_x);
	r->tex_x = (int)(r->wall_x * (double)TEX_SIZE);
	if ((r->side == 0 && r->dir_x > 0)
		|| (r->side == 1 && r->dir_y < 0))
		r->tex_x = TEX_SIZE - r->tex_x - 1;
	if (r->tex_x < 0)
		r->tex_x = 0;
	if (r->tex_x >= TEX_SIZE)
		r->tex_x = TEX_SIZE - 1;
}

static t_texture	*select_texture(t_game *game, t_ray *r)
{
	if (r->hit_cell == 'D' && game->has_door_tex)
		return (&game->door_tex);
	return (&game->tex[r->tex_num]);
}

static void	draw_textured(t_game *game, t_ray *r, int x)
{
	double		step;
	double		tex_pos;
	t_texture	*tex;
	int			y;
	int			tex_y;

	if (r->hit_cell == 'D' && !game->has_door_tex)
	{
		ft_draw_solid(game, r, x, 0x008B4513);
		return ;
	}
	step = (double)TEX_SIZE / (double)r->line_height;
	tex_pos = (r->draw_start - WIN_HEIGHT / 2
			+ r->line_height / 2) * step;
	tex = select_texture(game, r);
	y = r->draw_start;
	while (y < r->draw_end)
	{
		tex_y = (int)tex_pos & (TEX_SIZE - 1);
		tex_pos += step;
		ft_frame_put_pixel(game, x, y,
			tex->pixels[tex_y * TEX_SIZE + r->tex_x]);
		y++;
	}
}

void	ft_raycaster_draw_column(t_game *game, t_ray *r, int x)
{
	compute_height(r);
	compute_texture(r, &game->config->player);
	draw_textured(game, r, x);
}
