#!/usr/bin/env python3
"""Generate raycaster and player files for Tasks 4-5."""

import os

ROOT = '/home/z/my-project/cub3d'

def header(name):
    login = 'ruiferna'
    mail = 'ruiferna@student.42porto.com'
    created = '2025/07/10 19:00:00'
    updated = '2025/07/11 12:00:00'
    line4_name = name.ljust(51)
    by_content = f"{login} <{mail}>"
    line6_by = by_content.ljust(43)
    created_content = f"{created} by {login}"
    line8_created = created_content.ljust(41)
    updated_content = f"{updated} by {login}"
    line9_updated = updated_content.ljust(40)
    return (
        "/* ************************************************************************** */\n"
        "/*                                                                            */\n"
        "/*                                                        :::      ::::::::   */\n"
        f"/*   {line4_name}:+:      :+:    :+:   */\n"
        "/*                                                    +:+ +:+         +:+     */\n"
        f"/*   By: {line6_by}+#+  +:+       +#+        */\n"
        "/*                                                +#+#+#+#+#+   +#+           */\n"
        f"/*   Created: {line8_created}#+#    #+#             */\n"
        f"/*   Updated: {line9_updated}###   ########.fr       */\n"
        "/*                                                                            */\n"
        "/* ************************************************************************** */\n"
    )

def w(path, content):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, 'w') as f:
        f.write(content)
    print(f"  wrote {path}")

# ============================================================================
#  src/raycaster/raycaster.h
# ============================================================================
w(f'{ROOT}/src/raycaster/raycaster.h', header('raycaster.h') + """
#ifndef RAYCASTER_H
# define RAYCASTER_H

# include "cub3d.h"

void\traycaster_render(t_game *game);

#endif
""")

# ============================================================================
#  src/raycaster/raycaster.c — DDA main render loop (5 functions)
# ============================================================================
w(f'{ROOT}/src/raycaster/raycaster.c', header('raycaster.c') + """
#include "raycaster.h"
#include "../graphics/graphics.h"
#include <math.h>

/* Raycasting context for a single column. */
typedef struct s_ray
{
\tdouble\tcamera_x;
\tdouble\tdir_x;
\tdouble\tdir_y;
\tint\t\tmap_x;
\tint\t\tmap_y;
\tdouble\tside_dist_x;
\tdouble\tside_dist_y;
\tdouble\tdelta_dist_x;
\tdouble\tdelta_dist_y;
\tint\t\tstep_x;
\tint\t\tstep_y;
\tint\t\tside;
\tdouble\tperp_wall_dist;
\tint\t\tline_height;
\tint\t\tdraw_start;
\tint\t\tdraw_end;
\tint\t\ttex_num;
\tdouble\twall_x;
\tint\t\ttex_x;
}\t\t\tt_ray;

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
\t\tif (r->map_y < 0 || r->map_y >= map->height
\t\t\t|| r->map_x < 0 || r->map_x >= map->width
\t\t\t|| map->grid[r->map_y][r->map_x] == '1')
\t\t\thit = 1;
\t}
\tif (r->side == 0)
\t\tr->perp_wall_dist = r->side_dist_x - r->delta_dist_x;
\telse
\t\tr->perp_wall_dist = r->side_dist_y - r->delta_dist_y;
}

/* Computes wall height, draw range, texture index and tex_x. */
static void\tray_compute(t_ray *r, t_player *p)
{
\tr->line_height = (int)(WIN_HEIGHT / r->perp_wall_dist);
\tr->draw_start = -r->line_height / 2 + WIN_HEIGHT / 2;
\tif (r->draw_start < 0)
\t\tr->draw_start = 0;
\tr->draw_end = r->line_height / 2 + WIN_HEIGHT / 2;
\tif (r->draw_end >= WIN_HEIGHT)
\t\tr->draw_end = WIN_HEIGHT - 1;
\tif (r->side == 0)
\t{
\t\tif (r->dir_x > 0)
\t\t\tr->tex_num = TEX_EAST;
\t\telse
\t\t\tr->tex_num = TEX_WEST;
\t}
\telse
\t{
\t\tif (r->dir_y > 0)
\t\t\tr->tex_num = TEX_SOUTH;
\t\telse
\t\t\tr->tex_num = TEX_NORTH;
\t}
\tif (r->side == 0)
\t\tr->wall_x = p->y + r->perp_wall_dist * r->dir_y;
\telse
\t\tr->wall_x = p->x + r->perp_wall_dist * r->dir_x;
\tr->wall_x -= floor(r->wall_x);
\tr->tex_x = (int)(r->wall_x * (double)TEX_SIZE);
\tif ((r->side == 0 && r->dir_x > 0) || (r->side == 1 && r->dir_y < 0))
\t\tr->tex_x = TEX_SIZE - r->tex_x - 1;
}

/* Draws a single textured column at screen x. */
static void\tray_draw_column(t_game *game, t_ray *r, int x)
{
\tdouble\tstep;
\tdouble\ttex_pos;
\tint\t\ty;
\tint\t\ttex_y;
\tint\t\tcolor;
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
\t\tray_compute(&ray, &game->config->player);
\t\tray_draw_column(game, &ray, x);
\t\tx++;
\t}
}
""")

# ============================================================================
#  src/player/player.h
# ============================================================================
w(f'{ROOT}/src/player/player.h', header('player.h') + """
#ifndef PLAYER_H
# define PLAYER_H

# include "cub3d.h"

void\tplayer_init_direction(t_player *p);
void\tplayer_update(t_game *game);

#endif
""")

# ============================================================================
#  src/player/player.c — direction init + movement (5 functions)
# ============================================================================
w(f'{ROOT}/src/player/player.c', header('player.c') + """
#include "player.h"
#include "../graphics/graphics.h"
#include <math.h>

/* Initializes dir and plane vectors from the spawn direction. */
void\tplayer_init_direction(t_player *p)
{
\tif (p->direction == 'N')
\t{
\t\tp->dir_x = 0;
\t\tp->dir_y = -1;
\t\tp->plane_x = 0.66;
\t\tp->plane_y = 0;
\t}
\telse if (p->direction == 'S')
\t{
\t\tp->dir_x = 0;
\t\tp->dir_y = 1;
\t\tp->plane_x = -0.66;
\t\tp->plane_y = 0;
\t}
\telse if (p->direction == 'E')
\t{
\t\tp->dir_x = 1;
\t\tp->dir_y = 0;
\t\tp->plane_x = 0;
\t\tp->plane_y = 0.66;
\t}
\telse if (p->direction == 'W')
\t{
\t\tp->dir_x = -1;
\t\tp->dir_y = 0;
\t\tp->plane_x = 0;
\t\tp->plane_y = -0.66;
\t}
}

/* Returns 1 if (x, y) is a wall, 0 otherwise. Bounds-safe. */
static int\tis_wall(t_map *map, double x, double y)
{
\tint\tmx;
\tint\tmy;

\tif (x < 0 || y < 0)
\t\treturn (1);
\tmx = (int)x;
\tmy = (int)y;
\tif (my < 0 || my >= map->height || mx < 0 || mx >= map->width)
\t\treturn (1);
\treturn (map->grid[my][mx] == '1');
}

/* Attempts to move the player by (dx, dy) with collision check. */
static void\ttry_move(t_player *p, t_map *map, double dx, double dy)
{
\tif (!is_wall(map, p->x + dx + copysign(COLLISION_MARGIN, dx), p->y))
\t\tp->x += dx;
\tif (!is_wall(map, p->x, p->y + dy + copysign(COLLISION_MARGIN, dy)))
\t\tp->y += dy;
}

/* Rotates the player's dir and plane vectors by angle `rot`. */
static void\tplayer_rotate(t_player *p, double rot)
{
\tdouble\told_dir_x;
\tdouble\told_plane_x;

\told_dir_x = p->dir_x;
\tp->dir_x = p->dir_x * cos(rot) - p->dir_y * sin(rot);
\tp->dir_y = old_dir_x * sin(rot) + p->dir_y * cos(rot);
\told_plane_x = p->plane_x;
\tp->plane_x = p->plane_x * cos(rot) - p->plane_y * sin(rot);
\tp->plane_y = old_plane_x * sin(rot) + p->plane_y * cos(rot);
}

/* Processes all active key flags: movement and rotation. */
void\tplayer_update(t_game *game)
{
\tt_player\t*p;
\tt_keys\t\t*k;

\tp = &game->config->player;
\tk = &game->keys;
\tif (k->w)
\t\ttry_move(p, &game->config->map, p->dir_x * MOVE_SPEED,
\t\t\tp->dir_y * MOVE_SPEED);
\tif (k->s)
\t\ttry_move(p, &game->config->map, -p->dir_x * MOVE_SPEED,
\t\t\t-p->dir_y * MOVE_SPEED);
\tif (k->a)
\t\ttry_move(p, &game->config->map, -p->plane_x * MOVE_SPEED,
\t\t\t-p->plane_y * MOVE_SPEED);
\tif (k->d)
\t\ttry_move(p, &game->config->map, p->plane_x * MOVE_SPEED,
\t\t\tp->plane_y * MOVE_SPEED);
\tif (k->left)
\t\tplayer_rotate(p, -ROT_SPEED);
\tif (k->right)
\t\tplayer_rotate(p, ROT_SPEED);
}
""")

print("Raycaster and player files generated.")
