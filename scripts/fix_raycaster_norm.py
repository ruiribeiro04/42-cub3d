#!/usr/bin/env python3
"""Fix raycaster.c: move typedef to header, split long functions."""

import os

ROOT = '/home/z/my-project/cub3d'

def rd(p):
    with open(p) as f: return f.read()
def wr(p, c):
    with open(p, 'w') as f: f.write(c)
    print(f"  fixed {p}")

# === Move t_ray to raycaster.h ===
h = rd(f'{ROOT}/src/raycaster/raycaster.h')
h = h.replace(
    "void\traycaster_render(t_game *game);",
    "typedef struct s_ray\n"
    "{\n"
    "\tdouble\tcamera_x;\n"
    "\tdouble\tdir_x;\n"
    "\tdouble\tdir_y;\n"
    "\tint\t\tmap_x;\n"
    "\tint\t\tmap_y;\n"
    "\tdouble\tside_dist_x;\n"
    "\tdouble\tside_dist_y;\n"
    "\tdouble\tdelta_dist_x;\n"
    "\tdouble\tdelta_dist_y;\n"
    "\tint\t\tstep_x;\n"
    "\tint\t\tstep_y;\n"
    "\tint\t\tside;\n"
    "\tdouble\tperp_wall_dist;\n"
    "\tint\t\tline_height;\n"
    "\tint\t\tdraw_start;\n"
    "\tint\t\tdraw_end;\n"
    "\tint\t\ttex_num;\n"
    "\tdouble\twall_x;\n"
    "\tint\t\ttex_x;\n"
    "}\t\t\tt_ray;\n"
    "\n"
    "void\traycaster_render(t_game *game);"
)
wr(f'{ROOT}/src/raycaster/raycaster.h', h)

# === Rewrite raycaster.c without typedef, shorter functions ===
new_raycaster = """/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/11 12:00:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"
#include "../graphics/graphics.h"
#include <math.h>

/* Initializes the ray for column x. */
static void\tray_init(t_ray *r, t_player *p, int x)
{
\tr->camera_x = 2.0 * x / (double)WIN_WIDTH - 1.0;
\tr->dir_x = p->dir_x + p->plane_x * r->camera_x;
\tr->dir_y = p->dir_y + p->plane_y * r->camera_x;
\tr->map_x = (int)p->x;
\tr->map_y = (int)p->y;
\tif (r->dir_x == 0)
\t\tr->delta_dist_x = 1e30;
\telse
\t\tr->delta_dist_x = fabs(1.0 / r->dir_x);
\tif (r->dir_y == 0)
\t\tr->delta_dist_y = 1e30;
\telse
\t\tr->delta_dist_y = fabs(1.0 / r->dir_y);
}

/* Computes step direction and initial side_dist. */
static void\tray_step(t_ray *r, t_player *p)
{
\tif (r->dir_x < 0)
\t{
\t\tr->step_x = -1;
\t\tr->side_dist_x = (p->x - r->map_x) * r->delta_dist_x;
\t}
\telse
\t{
\t\tr->step_x = 1;
\t\tr->side_dist_x = (r->map_x + 1.0 - p->x) * r->delta_dist_x;
\t}
\tif (r->dir_y < 0)
\t{
\t\tr->step_y = -1;
\t\tr->side_dist_y = (p->y - r->map_y) * r->delta_dist_y;
\t}
\telse
\t{
\t\tr->step_y = 1;
\t\tr->side_dist_y = (r->map_y + 1.0 - p->y) * r->delta_dist_y;
\t}
}

/* Runs DDA until we hit a wall. Sets side and perp_wall_dist. */
static void\tray_dda(t_ray *r, t_map *map)
{
\tint\thit;

\thit = 0;
\twhile (!hit)
\t{
\t\tif (r->side_dist_x < r->side_dist_y)
\t\t{
\t\t\tr->side_dist_x += r->delta_dist_x;
\t\t\tr->map_x += r->step_x;
\t\t\tr->side = 0;
\t\t}
\t\telse
\t\t{
\t\t\tr->side_dist_y += r->delta_dist_y;
\t\t\tr->map_y += r->step_y;
\t\t\tr->side = 1;
\t\t}
\t\tif (r->map_y < 0 || r->map_y >= map->height)
\t\t\thit = 1;
\t\telse if (r->map_x < 0 || r->map_x >= map->width)
\t\t\thit = 1;
\t\telse if (map->grid[r->map_y][r->map_x] == '1')
\t\t\thit = 1;
\t}
\tif (r->side == 0)
\t\tr->perp_wall_dist = r->side_dist_x - r->delta_dist_x;
\telse
\t\tr->perp_wall_dist = r->side_dist_y - r->delta_dist_y;
}

/* Computes wall height and draw range. */
static void\tray_compute_height(t_ray *r)
{
\tr->line_height = (int)(WIN_HEIGHT / r->perp_wall_dist);
\tr->draw_start = -r->line_height / 2 + WIN_HEIGHT / 2;
\tif (r->draw_start < 0)
\t\tr->draw_start = 0;
\tr->draw_end = r->line_height / 2 + WIN_HEIGHT / 2;
\tif (r->draw_end >= WIN_HEIGHT)
\t\tr->draw_end = WIN_HEIGHT - 1;
}

/* Determines which texture to use and the tex_x coordinate. */
static void\tray_compute_texture(t_ray *r, t_player *p)
{
\tif (r->side == 0)
\t{
\t\tif (r->dir_x > 0)
\t\t\tr->tex_num = TEX_EAST;
\t\telse
\t\t\tr->tex_num = TEX_WEST;
\t\tr->wall_x = p->y + r->perp_wall_dist * r->dir_y;
\t}
\telse
\t{
\t\tif (r->dir_y > 0)
\t\t\tr->tex_num = TEX_SOUTH;
\t\telse
\t\t\tr->tex_num = TEX_NORTH;
\t\tr->wall_x = p->x + r->perp_wall_dist * r->dir_x;
\t}
\tr->wall_x -= floor(r->wall_x);
\tr->tex_x = (int)(r->wall_x * (double)TEX_SIZE);
\tif ((r->side == 0 && r->dir_x > 0) || (r->side == 1 && r->dir_y < 0))
\t\tr->tex_x = TEX_SIZE - r->tex_x - 1;
}

/* Draws a single textured column at screen x. */
static void\tray_draw_column(t_game *game, t_ray *r, int x)
{
\tdouble\t\tstep;
\tdouble\t\ttex_pos;
\tint\t\t\ty;
\tint\t\t\ttex_y;
\tint\t\t\tcolor;
\tt_texture\t*tex;

\tstep = (double)TEX_SIZE / (double)r->line_height;
\ttex_pos = (r->draw_start - WIN_HEIGHT / 2 + r->line_height / 2) * step;
\ttex = &game->tex[r->tex_num];
\ty = r->draw_start;
\twhile (y < r->draw_end)
\t{
\t\ttex_y = (int)tex_pos & (TEX_SIZE - 1);
\t\ttex_pos += step;
\t\tcolor = tex->pixels[tex_y * TEX_SIZE + r->tex_x];
\t\tif (r->side == 1)
\t\t\tcolor = (color >> 1) & 8355711;
\t\tframe_put_pixel(game, x, y, color);
\t\ty++;
\t}
}

/* Draws the floor and ceiling halves of the screen. */
static void\tdraw_floor_ceiling(t_game *game)
{
\tframe_fill_rect(game, 0, 0, WIN_WIDTH - 1, WIN_HEIGHT / 2 - 1,
\t\t\tgame->ceiling_color);
\tframe_fill_rect(game, 0, WIN_HEIGHT / 2, WIN_WIDTH - 1, WIN_HEIGHT - 1,
\t\t\tgame->floor_color);
}

/* Main render entry: clears, draws floor/ceiling, casts all rays. */
void\traycaster_render(t_game *game)
{
\tt_ray\tray;
\tint\t\tx;

\tdraw_floor_ceiling(game);
\tx = 0;
\twhile (x < WIN_WIDTH)
\t{
\t\tray_init(&ray, &game->config->player, x);
\t\tray_step(&ray, &game->config->player);
\t\tray_dda(&ray, &game->config->map);
\t\tray_compute_height(&ray);
\t\tray_compute_texture(&ray, &game->config->player);
\t\tray_draw_column(game, &ray, x);
\t\tx++;
\t}
}
"""
wr(f'{ROOT}/src/raycaster/raycaster.c', new_raycaster)

# === Fix player.c: player_init_direction is too long (split it) ===
p = rd(f'{ROOT}/src/player/player.c')
# Split player_init_direction into a helper that sets dir and plane
p = p.replace(
    "/* Initializes dir and plane vectors from the spawn direction. */\n"
    "void\tplayer_init_direction(t_player *p)\n"
    "{\n"
    "\tif (p->direction == 'N')\n"
    "\t{\n"
    "\t\tp->dir_x = 0;\n"
    "\t\tp->dir_y = -1;\n"
    "\t\tp->plane_x = 0.66;\n"
    "\t\tp->plane_y = 0;\n"
    "\t}\n"
    "\telse if (p->direction == 'S')\n"
    "\t{\n"
    "\t\tp->dir_x = 0;\n"
    "\t\tp->dir_y = 1;\n"
    "\t\tp->plane_x = -0.66;\n"
    "\t\tp->plane_y = 0;\n"
    "\t}\n"
    "\telse if (p->direction == 'E')\n"
    "\t{\n"
    "\t\tp->dir_x = 1;\n"
    "\t\tp->dir_y = 0;\n"
    "\t\tp->plane_x = 0;\n"
    "\t\tp->plane_y = 0.66;\n"
    "\t}\n"
    "\telse if (p->direction == 'W')\n"
    "\t{\n"
    "\t\tp->dir_x = -1;\n"
    "\t\tp->dir_y = 0;\n"
    "\t\tp->plane_x = 0;\n"
    "\t\tp->plane_y = -0.66;\n"
    "\t}\n"
    "}",
    "/* Sets dir/plane for N/S (vertical look). */\n"
    "static void\tset_vertical(t_player *p, int is_north)\n"
    "{\n"
    "\tp->dir_x = 0;\n"
    "\tp->plane_y = 0;\n"
    "\tp->plane_x = 0.66;\n"
    "\tif (is_north)\n"
    "\t\tp->dir_y = -1;\n"
    "\telse\n"
    "\t{\n"
    "\t\tp->dir_y = 1;\n"
    "\t\tp->plane_x = -0.66;\n"
    "\t}\n"
    "}\n"
    "\n"
    "/* Sets dir/plane for E/W (horizontal look). */\n"
    "static void\tset_horizontal(t_player *p, int is_east)\n"
    "{\n"
    "\tp->dir_y = 0;\n"
    "\tp->plane_x = 0;\n"
    "\tp->plane_y = 0.66;\n"
    "\tif (is_east)\n"
    "\t\tp->dir_x = 1;\n"
    "\telse\n"
    "\t{\n"
    "\t\tp->dir_x = -1;\n"
    "\t\tp->plane_y = -0.66;\n"
    "\t}\n"
    "}\n"
    "\n"
    "/* Initializes dir and plane vectors from spawn direction. */\n"
    "void\tplayer_init_direction(t_player *p)\n"
    "{\n"
    "\tif (p->direction == 'N')\n"
    "\t\tset_vertical(p, 1);\n"
    "\telse if (p->direction == 'S')\n"
    "\t\tset_vertical(p, 0);\n"
    "\telse if (p->direction == 'E')\n"
    "\t\tset_horizontal(p, 1);\n"
    "\telse if (p->direction == 'W')\n"
    "\t\tset_horizontal(p, 0);\n"
    "}"
)
wr(f'{ROOT}/src/player/player.c', p)

print("Raycaster and player norminette fixes applied.")
