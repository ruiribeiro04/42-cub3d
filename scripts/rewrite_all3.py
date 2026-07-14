#!/usr/bin/env python3
"""Part 3: raycaster, player, bonus files."""

import os

ROOT = '/home/z/my-project/cub3d'

def h(name):
    login = 'ruiferna'
    mail = 'ruiferna@student.42porto.com'
    created = '2025/07/10 19:00:00'
    updated = '2025/07/11 16:00:00'
    n = name.ljust(51)
    by = f"{login} <{mail}>".ljust(43)
    cr = f"{created} by {login}".ljust(41)
    up = f"{updated} by {login}".ljust(40)
    return (
        "/* ************************************************************************** */\n"
        "/*                                                                            */\n"
        "/*                                                        :::      ::::::::   */\n"
        f"/*   {n}:+:      :+:    :+:   */\n"
        "/*                                                    +:+ +:+         +:+     */\n"
        f"/*   By: {by}+#+  +:+       +#+        */\n"
        "/*                                                +#+#+#+#+#+   +#+           */\n"
        f"/*   Created: {cr}#+#    #+#             */\n"
        f"/*   Updated: {up}###   ########.fr       */\n"
        "/*                                                                            */\n"
        "/* ************************************************************************** */\n"
    )

def w(path, content):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, 'w') as f:
        f.write(content)
    print(f"  wrote {path}")

# =====================================================================
#  src/raycaster/raycaster.h
# =====================================================================
w(f'{ROOT}/src/raycaster/raycaster.h', h('raycaster.h') + r"""#ifndef RAYCASTER_H
# define RAYCASTER_H

# include "cub3d.h"

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_num;
	double	wall_x;
	int		tex_x;
	char	hit_cell;
}			t_ray;

void	raycaster_render(t_game *game);
void	raycaster_clear(t_game *game);
void	raycaster_draw_column(t_game *game, t_ray *r, int x);

#endif
""")

# =====================================================================
#  src/raycaster/raycaster.c — DDA stops on '1' and 'D', z_buffer
# =====================================================================
w(f'{ROOT}/src/raycaster/raycaster.c', h('raycaster.c') + r"""#include "raycaster.h"
#include "../graphics/graphics.h"
#include <math.h>

static void	ray_init(t_ray *r, t_player *p, int x)
{
	r->camera_x = 2.0 * x / (double)WIN_WIDTH - 1.0;
	r->dir_x = p->dir_x + p->plane_x * r->camera_x;
	r->dir_y = p->dir_y + p->plane_y * r->camera_x;
	r->map_x = (int)p->x;
	r->map_y = (int)p->y;
	if (r->dir_x == 0)
		r->delta_dist_x = 1e30;
	else
		r->delta_dist_x = fabs(1.0 / r->dir_x);
	if (r->dir_y == 0)
		r->delta_dist_y = 1e30;
	else
		r->delta_dist_y = fabs(1.0 / r->dir_y);
}

static void	ray_step(t_ray *r, t_player *p)
{
	if (r->dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (p->x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - p->x) * r->delta_dist_x;
	}
	if (r->dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (p->y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - p->y) * r->delta_dist_y;
	}
}

static int	dda_advance(t_ray *r, t_map *map)
{
	char	cell;

	if (r->side_dist_x < r->side_dist_y)
	{
		r->side_dist_x += r->delta_dist_x;
		r->map_x += r->step_x;
		r->side = 0;
	}
	else
	{
		r->side_dist_y += r->delta_dist_y;
		r->map_y += r->step_y;
		r->side = 1;
	}
	if (r->map_y < 0 || r->map_y >= map->height)
		return (1);
	if (r->map_x < 0 || r->map_x >= map->width)
		return (1);
	cell = map->grid[r->map_y][r->map_x];
	if (cell == '1' || cell == 'D')
	{
		r->hit_cell = cell;
		return (1);
	}
	return (0);
}

static void	ray_dda(t_ray *r, t_map *map)
{
	int	hit;

	hit = 0;
	while (!hit)
		hit = dda_advance(r, map);
	if (r->side == 0)
		r->perp_wall_dist = r->side_dist_x - r->delta_dist_x;
	else
		r->perp_wall_dist = r->side_dist_y - r->delta_dist_y;
}

void	raycaster_render(t_game *game)
{
	t_ray	ray;
	int		x;

	raycaster_clear(game);
	x = 0;
	while (x < WIN_WIDTH)
	{
		ray_init(&ray, &game->config->player, x);
		ray_step(&ray, &game->config->player);
		ray_dda(&ray, &game->config->map);
		raycaster_draw_column(game, &ray, x);
		if (game->z_buffer)
			game->z_buffer[x] = ray.perp_wall_dist;
		x++;
	}
}
""")

# =====================================================================
#  src/raycaster/raycaster_draw.c — door texture support
# =====================================================================
w(f'{ROOT}/src/raycaster/raycaster_draw.c', h('raycaster_draw.c') + r"""#include "raycaster.h"
#include "../graphics/graphics.h"
#include <math.h>

static void	compute_height(t_ray *r)
{
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

	step = (double)TEX_SIZE / (double)r->line_height;
	tex_pos = (r->draw_start - WIN_HEIGHT / 2
			+ r->line_height / 2) * step;
	tex = select_texture(game, r);
	y = r->draw_start;
	while (y < r->draw_end)
	{
		tex_y = (int)tex_pos & (TEX_SIZE - 1);
		tex_pos += step;
		frame_put_pixel(game, x, y,
			tex->pixels[tex_y * TEX_SIZE + r->tex_x]);
		y++;
	}
}

void	raycaster_clear(t_game *game)
{
	t_rect	top;
	t_rect	bottom;

	top.x0 = 0;
	top.y0 = 0;
	top.x1 = WIN_WIDTH - 1;
	top.y1 = WIN_HEIGHT / 2 - 1;
	bottom.x0 = 0;
	bottom.y0 = WIN_HEIGHT / 2;
	bottom.x1 = WIN_WIDTH - 1;
	bottom.y1 = WIN_HEIGHT - 1;
	frame_fill_rect(game, top, game->ceiling_color);
	frame_fill_rect(game, bottom, game->floor_color);
}

void	raycaster_draw_column(t_game *game, t_ray *r, int x)
{
	compute_height(r);
	compute_texture(r, &game->config->player);
	draw_textured(game, r, x);
}
""")

# =====================================================================
#  src/player/player.h
# =====================================================================
w(f'{ROOT}/src/player/player.h', h('player.h') + r"""#ifndef PLAYER_H
# define PLAYER_H

# include "cub3d.h"

void	player_init_direction(t_player *p);
void	player_update(t_game *game);
void	apply_movement(t_game *game, t_player *p, t_keys *k);

#endif
""")

# =====================================================================
#  src/player/player.c
# =====================================================================
w(f'{ROOT}/src/player/player.c', h('player.c') + r"""#include "player.h"
#include "../graphics/graphics.h"

static void	set_vertical(t_player *p, int is_north)
{
	p->dir_x = 0;
	p->plane_y = 0;
	p->plane_x = 0.66;
	if (is_north)
		p->dir_y = -1;
	else
	{
		p->dir_y = 1;
		p->plane_x = -0.66;
	}
}

static void	set_horizontal(t_player *p, int is_east)
{
	p->dir_y = 0;
	p->plane_x = 0;
	p->plane_y = 0.66;
	if (is_east)
		p->dir_x = 1;
	else
	{
		p->dir_x = -1;
		p->plane_y = -0.66;
	}
}

void	player_init_direction(t_player *p)
{
	if (p->direction == 'N')
		set_vertical(p, 1);
	else if (p->direction == 'S')
		set_vertical(p, 0);
	else if (p->direction == 'E')
		set_horizontal(p, 1);
	else if (p->direction == 'W')
		set_horizontal(p, 0);
}
""")

# =====================================================================
#  src/player/player_move.c
# =====================================================================
w(f'{ROOT}/src/player/player_move.c', h('player_move.c') + r"""#include "player.h"
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
""")

# =====================================================================
#  src/player/player_apply.c
# =====================================================================
w(f'{ROOT}/src/player/player_apply.c', h('player_apply.c') + r"""#include "player.h"
#include "../graphics/graphics.h"

static int	is_wall(t_map *map, double x, double y)
{
	int	mx;
	int	my;

	if (x < 0 || y < 0)
		return (1);
	mx = (int)x;
	my = (int)y;
	if (my < 0 || my >= map->height || mx < 0 || mx >= map->width)
		return (1);
	return (map->grid[my][mx] == '1' || map->grid[my][mx] == 'D');
}

static void	try_move_x(t_player *p, t_map *map, double dx)
{
	double	margin;

	margin = COLLISION_MARGIN;
	if (dx < 0)
		margin = -margin;
	if (!is_wall(map, p->x + dx + margin, p->y))
		p->x += dx;
}

static void	try_move_y(t_player *p, t_map *map, double dy)
{
	double	margin;

	margin = COLLISION_MARGIN;
	if (dy < 0)
		margin = -margin;
	if (!is_wall(map, p->x, p->y + dy + margin))
		p->y += dy;
}

void	apply_movement(t_game *game, t_player *p, t_keys *k)
{
	if (k->w)
	{
		try_move_x(p, &game->config->map, p->dir_x * MOVE_SPEED);
		try_move_y(p, &game->config->map, p->dir_y * MOVE_SPEED);
	}
	if (k->s)
	{
		try_move_x(p, &game->config->map, -p->dir_x * MOVE_SPEED);
		try_move_y(p, &game->config->map, -p->dir_y * MOVE_SPEED);
	}
	if (k->a)
	{
		try_move_x(p, &game->config->map, -p->plane_x * MOVE_SPEED);
		try_move_y(p, &game->config->map, -p->plane_y * MOVE_SPEED);
	}
	if (k->d)
	{
		try_move_x(p, &game->config->map, p->plane_x * MOVE_SPEED);
		try_move_y(p, &game->config->map, p->plane_y * MOVE_SPEED);
	}
}
""")

# =====================================================================
#  src/bonus/bonus.h
# =====================================================================
w(f'{ROOT}/src/bonus/bonus.h', h('bonus.h') + r"""#ifndef BONUS_H
# define BONUS_H

# include "cub3d.h"

# define MINIMAP_TILE 8
# define MINIMAP_X 10
# define MINIMAP_Y 10

void	minimap_draw(t_game *game);
int		door_toggle(t_game *game, int mx, int my);
void	door_try_front(t_game *game);
int		hook_mouse_move(int x, int y, t_game *game);

#endif
""")

# =====================================================================
#  src/bonus/sprites.h
# =====================================================================
w(f'{ROOT}/src/bonus/sprites.h', h('sprites.h') + r"""#ifndef SPRITES_H
# define SPRITES_H

# include "cub3d.h"

typedef struct s_sprite_draw
{
	int		screen_x;
	int		sprite_height;
	int		sprite_width;
	int		draw_start_y;
	int		draw_end_y;
	int		draw_start_x;
	int		draw_end_x;
}			t_sprite_draw;

typedef struct s_stripe_ctx
{
	t_game			*g;
	t_sprite_draw	*d;
	int				stripe;
	int				tex_x;
	double			ty;
}			t_stripe_ctx;

void	sprites_render(t_game *game);
void	draw_sprite_stripes(t_game *g, t_sprite_draw *d, double ty);
void	sprites_update(t_game *game);
void	sprites_sort(t_game *game);
int		sprites_init(t_game *game);

#endif
""")

# =====================================================================
#  src/bonus/minimap.c — triangle player indicator
# =====================================================================
w(f'{ROOT}/src/bonus/minimap.c', h('minimap.c') + r"""#include "bonus.h"
#include "../graphics/graphics.h"

static void	draw_tile(t_game *g, int mx, int my, int color)
{
	t_rect	r;
	int		sx;
	int		sy;

	sx = MINIMAP_X + mx * MINIMAP_TILE;
	sy = MINIMAP_Y + my * MINIMAP_TILE;
	r.x0 = sx;
	r.y0 = sy;
	r.x1 = sx + MINIMAP_TILE - 1;
	r.y1 = sy + MINIMAP_TILE - 1;
	frame_fill_rect(g, r, color);
}

static void	draw_player_dir_line(t_game *g, t_player *p,
									int cx, int cy)
{
	int	i;
	int	px;
	int	py;

	i = 0;
	while (i < 6)
	{
		px = cx + (int)(p->dir_x * i);
		py = cy + (int)(p->dir_y * i);
		frame_put_pixel(g, px, py, 0x00FFFF00);
		frame_put_pixel(g, px + 1, py, 0x00FFFF00);
		frame_put_pixel(g, px, py + 1, 0x00FFFF00);
		i++;
	}
}

static void	draw_player_marker(t_game *g)
{
	t_player	*p;
	int			cx;
	int			cy;

	p = &g->config->player;
	cx = MINIMAP_X + (int)(p->x * MINIMAP_TILE) + MINIMAP_TILE / 2;
	cy = MINIMAP_Y + (int)(p->y * MINIMAP_TILE) + MINIMAP_TILE / 2;
	frame_put_pixel(g, cx, cy, 0x00FF0000);
	frame_put_pixel(g, cx + 1, cy, 0x00FF0000);
	frame_put_pixel(g, cx - 1, cy, 0x00FF0000);
	frame_put_pixel(g, cx, cy + 1, 0x00FF0000);
	frame_put_pixel(g, cx, cy - 1, 0x00FF0000);
	draw_player_dir_line(g, p, cx, cy);
}

void	minimap_draw(t_game *game)
{
	int		x;
	int		y;
	int		color;
	char	cell;

	y = 0;
	while (y < game->config->map.height)
	{
		x = 0;
		while (x < game->config->map.width)
		{
			cell = game->config->map.grid[y][x];
			if (cell == '1')
				color = 0x00FFFFFF;
			else if (cell == 'D')
				color = 0x00AA6600;
			else if (cell == 'O')
				color = 0x0000AA00;
			else
				color = 0x00444444;
			draw_tile(game, x, y, color);
			x++;
		}
		y++;
	}
	draw_player_marker(game);
}
""")

# =====================================================================
#  src/bonus/doors.c — check 4 adjacent cells
# =====================================================================
w(f'{ROOT}/src/bonus/doors.c', h('doors.c') + r"""#include "bonus.h"
#include "../graphics/graphics.h"

static int	in_bounds(t_map *map, int mx, int my)
{
	if (my < 0 || my >= map->height)
		return (0);
	if (mx < 0 || mx >= map->width)
		return (0);
	return (1);
}

int	door_toggle(t_game *game, int mx, int my)
{
	t_map	*map;
	char	cell;

	map = &game->config->map;
	if (!in_bounds(map, mx, my))
		return (0);
	cell = map->grid[my][mx];
	if (cell == 'D')
		map->grid[my][mx] = 'O';
	else if (cell == 'O')
		map->grid[my][mx] = 'D';
	else
		return (0);
	return (1);
}

void	door_try_front(t_game *game)
{
	t_player	*p;
	int			px;
	int			py;

	p = &game->config->player;
	px = (int)p->x;
	py = (int)p->y;
	if (door_toggle(game, px + 1, py))
		return ;
	if (door_toggle(game, px - 1, py))
		return ;
	if (door_toggle(game, px, py + 1))
		return ;
	if (door_toggle(game, px, py - 1))
		return ;
}
""")

# =====================================================================
#  src/bonus/mouse.c — delta from center
# =====================================================================
w(f'{ROOT}/src/bonus/mouse.c', h('mouse.c') + r"""#include "bonus.h"
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
		rotate_player(&game->config->player,
			(double)delta * MOUSE_SENS);
	return (0);
}
""")

# =====================================================================
#  src/bonus/sprites.c — use sprite_frames array
# =====================================================================
w(f'{ROOT}/src/bonus/sprites.c', h('sprites.c') + r"""#include "sprites.h"
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
""")

# =====================================================================
#  src/bonus/sprites_draw.c — use sprite_frames[frame]
# =====================================================================
w(f'{ROOT}/src/bonus/sprites_draw.c', h('sprites_draw.c') + r"""#include "sprites.h"
#include "../graphics/graphics.h"

static int	compute_tex_x(t_sprite_draw *d, int stripe)
{
	int	base;

	base = stripe - (-d->sprite_width / 2 + d->screen_x);
	return ((int)(256 * base * TEX_SIZE / d->sprite_width / 256));
}

static void	draw_one_pixel(t_stripe_ctx *c, int y)
{
	int	tex_y;
	int	color;

	tex_y = (y * 256 - WIN_HEIGHT * 128 + c->d->sprite_height * 128)
		/ c->d->sprite_height / 256;
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
""")

# =====================================================================
#  src/bonus/sprite_anim.c — cycle num_sprite_frames
# =====================================================================
w(f'{ROOT}/src/bonus/sprite_anim.c', h('sprite_anim.c') + r"""#include "sprites.h"
#include "../graphics/graphics.h"

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
	if (!game->has_sprites)
		return ;
	game->sprite_anim_counter++;
	if (game->sprite_anim_counter >= SPRITE_ANIM_DELAY)
	{
		game->sprite_anim_counter = 0;
		game->sprite_frame = (game->sprite_frame + 1)
			% game->num_sprite_frames;
	}
}
""")

# =====================================================================
#  src/bonus/sprites_init.c
# =====================================================================
w(f'{ROOT}/src/bonus/sprites_init.c', h('sprites_init.c') + r"""#include "sprites.h"
#include "../graphics/graphics.h"
#include <stdlib.h>

int	sprites_init(t_game *game)
{
	t_config	*cfg;
	int			i;

	cfg = game->config;
	if (!cfg->has_sprite || cfg->num_sprites == 0)
	{
		game->has_sprites = 0;
		return (0);
	}
	game->sprites = (t_sprite *)malloc(
			sizeof(t_sprite) * cfg->num_sprites);
	if (!game->sprites)
		return (cub_error_int("Failed to alloc sprites"));
	i = 0;
	while (i < cfg->num_sprites)
	{
		game->sprites[i].x = cfg->sprite_positions[i].x;
		game->sprites[i].y = cfg->sprite_positions[i].y;
		game->sprites[i].distance = 0.0;
		i++;
	}
	game->num_sprites = cfg->num_sprites;
	game->has_sprites = 1;
	game->sprite_frame = 0;
	game->sprite_anim_counter = 0;
	return (0);
}
""")

print("=== Part 3 done (raycaster + player + bonus) ===")
