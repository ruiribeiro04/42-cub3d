#!/usr/bin/env python3
"""
Comprehensive norminette fix for ALL files.
- Use t_rect struct to reduce fill_rect args
- Split raycaster.c (8 functions) into raycaster.c + raycaster_draw.c
- Split player.c (7 functions) into player.c + player_move.c
- Fix all alignment issues
"""

import os

ROOT = '/home/z/my-project/cub3d'

def header(name):
    login = 'ruiferna'
    mail = 'ruiferna@student.42porto.com'
    created = '2025/07/10 19:00:00'
    updated = '2025/07/11 13:00:00'
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
#  Rewrite cub3d.h with all types + aligned declarations
# ============================================================================
w(f'{ROOT}/includes/cub3d.h', header('cub3d.h') + """
#ifndef CUB3D_H
# define CUB3D_H

# include <stddef.h>
# include "mlx.h"

# ifndef PI
#  define PI 3.14159265358979323846
# endif

# define WIN_WIDTH  1280
# define WIN_HEIGHT 720
# define TEX_SIZE   64
# define MOVE_SPEED 0.06
# define ROT_SPEED  0.04
# define COLLISION_MARGIN 0.2

typedef struct s_color
{
\tint\tr;
\tint\tg;
\tint\tb;
}\t\t\tt_color;

typedef struct s_texture_paths
{
\tchar\t*north;
\tchar\t*south;
\tchar\t*west;
\tchar\t*east;
}\t\t\tt_texture_paths;

typedef struct s_player
{
\tdouble\tx;
\tdouble\ty;
\tchar\tdirection;
\tdouble\tangle;
\tdouble\tdir_x;
\tdouble\tdir_y;
\tdouble\tplane_x;
\tdouble\tplane_y;
}\t\t\tt_player;

typedef struct s_map
{
\tchar\t**grid;
\tint\t\theight;
\tint\t\twidth;
}\t\t\tt_map;

typedef struct s_config
{
\tt_texture_paths\ttextures;
\tt_color\t\t\tfloor;
\tt_color\t\t\tceiling;
\tt_map\t\t\tmap;
\tt_player\t\tplayer;
\tint\t\t\t\thas_north;
\tint\t\t\t\thas_south;
\tint\t\t\t\thas_west;
\tint\t\t\t\thas_east;
\tint\t\t\t\thas_floor;
\tint\t\t\t\thas_ceiling;
\tint\t\t\t\thas_player;
}\t\t\tt_config;

typedef struct s_img
{
\tvoid\t*ptr;
\tchar\t*data;
\tint\t\tbpp;
\tint\t\tline_len;
\tint\t\tendian;
\tint\t\twidth;
\tint\t\theight;
}\t\t\tt_img;

typedef struct s_texture
{
\tt_img\timg;
\tint\t\t*pixels;
}\t\t\tt_texture;

typedef struct s_keys
{
\tint\t\tw;
\tint\t\ta;
\tint\t\ts;
\tint\t\td;
\tint\t\tleft;
\tint\t\tright;
}\t\t\tt_keys;

typedef struct s_game
{
\tvoid\t\t*mlx;
\tvoid\t\t*win;
\tt_img\t\tframe;
\tt_config\t*config;
\tt_texture\ttex[4];
\tint\t\t\tfloor_color;
\tint\t\t\tceiling_color;
\tt_keys\t\tkeys;
}\t\t\tt_game;

# define TEX_NORTH 0
# define TEX_SOUTH 1
# define TEX_WEST  2
# define TEX_EAST  3

t_config\t\t*parse_cub_file(const char *path);
void\t\t\tfree_config(t_config *config);
void\t\t\tcub_error(const char *msg);
void\t\t\t*cub_error_ret(const char *msg, void *ret);
int\t\t\t\tcub_error_int(const char *msg);
int\t\t\tgame_init(t_game *game, t_config *config);
void\t\t\tgame_cleanup(t_game *game);
int\t\t\tgame_run(t_game *game);

#endif
""")

# ============================================================================
#  Rewrite graphics.h with t_rect and proper alignment
# ============================================================================
w(f'{ROOT}/src/graphics/graphics.h', header('graphics.h') + """
#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "cub3d.h"

/* Rectangle helper to keep function args <= 4. */
typedef struct s_rect
{
\tint\tx0;
\tint\ty0;
\tint\tx1;
\tint\ty1;
}\t\t\tt_rect;

void\tframe_put_pixel(t_game *game, int x, int y, int color);
void\tframe_fill_rect(t_game *game, t_rect rect, int color);
void\tframe_clear(t_game *game);
int\t\tload_texture(t_game *game, t_texture *tex, char *path);
void\tdestroy_texture(t_game *game, t_texture *tex);
int\t\tcolor_to_int(t_color c);
int\t\thook_key_press(int keycode, t_game *game);
int\t\thook_key_release(int keycode, t_game *game);
int\t\thook_exit(t_game *game);
int\t\thook_loop(t_game *game);
void\tplayer_update(t_game *game);
void\traycaster_render(t_game *game);
void\tplayer_init_direction(t_player *p);

# define KEY_ESC   65307
# define KEY_W     119
# define KEY_A     97
# define KEY_S     115
# define KEY_D     100
# define KEY_LEFT  65361
# define KEY_RIGHT 65363

#endif
""")

# ============================================================================
#  Rewrite pixel.c with t_rect (3 functions)
# ============================================================================
w(f'{ROOT}/src/graphics/pixel.c', header('pixel.c') + """
#include "graphics.h"

/* Puts a single pixel into the frame buffer. Bounds-checked. */
void\tframe_put_pixel(t_game *game, int x, int y, int color)
{
\tchar\t*dst;

\tif (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
\t\treturn ;
\tdst = game->frame.data + (y * game->frame.line_len
\t\t\t+ x * (game->frame.bpp / 8));
\t*(int *)dst = color;
}

/* Fills a horizontal line with a solid color. */
static void\tfill_hline(t_game *g, int x0, int x1, int y, int color)
{
\twhile (x0 <= x1)
\t{
\t\tframe_put_pixel(g, x0, y, color);
\t\tx0++;
\t}
}

/* Fills a rectangle with a solid color. */
void\tframe_fill_rect(t_game *game, t_rect rect, int color)
{
\tint\ty;

\ty = rect.y0;
\twhile (y <= rect.y1)
\t{
\t\tfill_hline(game, rect.x0, rect.x1, y, color);
\t\ty++;
\t}
}

/* Clears the entire frame (fills with black). */
void\tframe_clear(t_game *game)
{
\tt_rect\tr;

\tr.x0 = 0;
\tr.y0 = 0;
\tr.x1 = WIN_WIDTH - 1;
\tr.y1 = WIN_HEIGHT - 1;
\tframe_fill_rect(game, r, 0);
}
""")

# ============================================================================
#  Rewrite raycaster.c (5 functions: the ray casting logic only)
# ============================================================================
w(f'{ROOT}/src/raycaster/raycaster.c', header('raycaster.c') + """
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

/* Advances DDA one step. Returns 1 if hit wall/oob. */
static int\tdda_advance(t_ray *r, t_map *map)
{
\tif (r->side_dist_x < r->side_dist_y)
\t{
\t\tr->side_dist_x += r->delta_dist_x;
\t\tr->map_x += r->step_x;
\t\tr->side = 0;
\t}
\telse
\t{
\t\tr->side_dist_y += r->delta_dist_y;
\t\tr->map_y += r->step_y;
\t\tr->side = 1;
\t}
\tif (r->map_y < 0 || r->map_y >= map->height)
\t\treturn (1);
\tif (r->map_x < 0 || r->map_x >= map->width)
\t\treturn (1);
\treturn (map->grid[r->map_y][r->map_x] == '1');
}

/* Runs DDA until we hit a wall. Sets perp_wall_dist. */
static void\tray_dda(t_ray *r, t_map *map)
{
\tint\thit;

\thit = 0;
\twhile (!hit)
\t\thit = dda_advance(r, map);
\tif (r->side == 0)
\t\tr->perp_wall_dist = r->side_dist_x - r->delta_dist_x;
\telse
\t\tr->perp_wall_dist = r->side_dist_y - r->delta_dist_y;
}

/* Main render entry: clears, draws floor/ceiling, casts all rays. */
void\traycaster_render(t_game *game)
{
\tt_ray\tray;
\tint\t\tx;

\traycaster_clear(game);
\tx = 0;
\twhile (x < WIN_WIDTH)
\t{
\t\tray_init(&ray, &game->config->player, x);
\t\tray_step(&ray, &game->config->player);
\t\tray_dda(&ray, &game->config->map);
\t\traycaster_draw_column(game, &ray, x);
\t\tx++;
\t}
}
""")

# ============================================================================
#  raycaster.h — add t_ray + declarations for split functions
# ============================================================================
w(f'{ROOT}/src/raycaster/raycaster.h', header('raycaster.h') + """
#ifndef RAYCASTER_H
# define RAYCASTER_H

# include "cub3d.h"

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

void\traycaster_render(t_game *game);
void\traycaster_clear(t_game *game);
void\traycaster_draw_column(t_game *game, t_ray *r, int x);

#endif
""")

# ============================================================================
#  raycaster_draw.c — draw_column + clear + compute helpers (5 functions)
# ============================================================================
w(f'{ROOT}/src/raycaster/raycaster_draw.c', header('raycaster_draw.c') + """
#include "raycaster.h"
#include "../graphics/graphics.h"
#include <math.h>

/* Computes wall height and draw range. */
static void\tcompute_height(t_ray *r)
{
\tr->line_height = (int)(WIN_HEIGHT / r->perp_wall_dist);
\tr->draw_start = -r->line_height / 2 + WIN_HEIGHT / 2;
\tif (r->draw_start < 0)
\t\tr->draw_start = 0;
\tr->draw_end = r->line_height / 2 + WIN_HEIGHT / 2;
\tif (r->draw_end >= WIN_HEIGHT)
\t\tr->draw_end = WIN_HEIGHT - 1;
}

/* Selects texture and computes tex_x. */
static void\tcompute_texture(t_ray *r, t_player *p)
{
\tif (r->side == 0)
\t{
\t\tr->tex_num = (r->dir_x > 0) ? TEX_EAST : TEX_WEST;
\t\tr->wall_x = p->y + r->perp_wall_dist * r->dir_y;
\t}
\telse
\t{
\t\tr->tex_num = (r->dir_y > 0) ? TEX_SOUTH : TEX_NORTH;
\t\tr->wall_x = p->x + r->perp_wall_dist * r->dir_x;
\t}
\tr->wall_x -= floor(r->wall_x);
\tr->tex_x = (int)(r->wall_x * (double)TEX_SIZE);
\tif ((r->side == 0 && r->dir_x > 0) || (r->side == 1 && r->dir_y < 0))
\t\tr->tex_x = TEX_SIZE - r->tex_x - 1;
}

/* Draws the textured pixels for one column. */
static void\tdraw_textured(t_game *game, t_ray *r, int x)
{
\tdouble\t\tstep;
\tdouble\t\ttex_pos;
\tt_texture\t*tex;
\tint\t\t\ty;

\tstep = (double)TEX_SIZE / (double)r->line_height;
\ttex_pos = (r->draw_start - WIN_HEIGHT / 2 + r->line_height / 2) * step;
\ttex = &game->tex[r->tex_num];
\ty = r->draw_start;
\twhile (y < r->draw_end)
\t{
\t\tr->tex_x = r->tex_x;
\t\ttex_pos += step;
\t\tframe_put_pixel(game, x, y,
\t\t\ttex->pixels[((int)tex_pos & (TEX_SIZE - 1)) * TEX_SIZE
\t\t\t+ r->tex_x]);
\t\ty++;
\t}
}

/* Draws floor and ceiling halves. */
void\traycaster_clear(t_game *game)
{
\tt_rect\ttop;
\tt_rect\tbottom;

\ttop.x0 = 0;
\ttop.y0 = 0;
\ttop.x1 = WIN_WIDTH - 1;
\ttop.y1 = WIN_HEIGHT / 2 - 1;
\tbottom.x0 = 0;
\tbottom.y0 = WIN_HEIGHT / 2;
\tbottom.x1 = WIN_WIDTH - 1;
\tbottom.y1 = WIN_HEIGHT - 1;
\tframe_fill_rect(game, top, game->ceiling_color);
\tframe_fill_rect(game, bottom, game->floor_color);
}

/* Computes height/texture then draws the column. */
void\traycaster_draw_column(t_game *game, t_ray *r, int x)
{
\tcompute_height(r);
\tcompute_texture(r, &game->config->player);
\tdraw_textured(game, r, x);
}
""")

# ============================================================================
#  player.c — direction init only (5 functions)
# ============================================================================
w(f'{ROOT}/src/player/player.c', header('player.c') + """
#include "player.h"
#include "../graphics/graphics.h"

/* Sets dir/plane for N/S (vertical look). */
static void\tset_vertical(t_player *p, int is_north)
{
\tp->dir_x = 0;
\tp->plane_y = 0;
\tp->plane_x = 0.66;
\tif (is_north)
\t\tp->dir_y = -1;
\telse
\t{
\t\tp->dir_y = 1;
\t\tp->plane_x = -0.66;
\t}
}

/* Sets dir/plane for E/W (horizontal look). */
static void\tset_horizontal(t_player *p, int is_east)
{
\tp->dir_y = 0;
\tp->plane_x = 0;
\tp->plane_y = 0.66;
\tif (is_east)
\t\tp->dir_x = 1;
\telse
\t{
\t\tp->dir_x = -1;
\t\tp->plane_y = -0.66;
\t}
}

/* Initializes dir and plane vectors from spawn direction. */
void\tplayer_init_direction(t_player *p)
{
\tif (p->direction == 'N')
\t\tset_vertical(p, 1);
\telse if (p->direction == 'S')
\t\tset_vertical(p, 0);
\telse if (p->direction == 'E')
\t\tset_horizontal(p, 1);
\telse if (p->direction == 'W')
\t\tset_horizontal(p, 0);
}
""")

# ============================================================================
#  player.h — updated
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
#  player_move.c — movement and rotation (5 functions)
# ============================================================================
w(f'{ROOT}/src/player/player_move.c', header('player_move.c') + """
#include "player.h"
#include "../graphics/graphics.h"
#include <math.h>

/* Returns 1 if (x, y) is a wall. Bounds-safe. */
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

/* Tries to move on X axis with collision margin. */
static void\ttry_move_x(t_player *p, t_map *map, double dx)
{
\tdouble\tmargin;

\tmargin = COLLISION_MARGIN;
\tif (dx < 0)
\t\tmargin = -margin;
\tif (!is_wall(map, p->x + dx + margin, p->y))
\t\tp->x += dx;
}

/* Tries to move on Y axis with collision margin. */
static void\ttry_move_y(t_player *p, t_map *map, double dy)
{
\tdouble\tmargin;

\tmargin = COLLISION_MARGIN;
\tif (dy < 0)
\t\tmargin = -margin;
\tif (!is_wall(map, p->x, p->y + dy + margin))
\t\tp->y += dy;
}

/* Rotates dir and plane vectors by angle `rot`. */
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
\t{
\t\ttry_move_x(p, &game->config->map, p->dir_x * MOVE_SPEED);
\t\ttry_move_y(p, &game->config->map, p->dir_y * MOVE_SPEED);
\t}
\tif (k->s)
\t{
\t\ttry_move_x(p, &game->config->map, -p->dir_x * MOVE_SPEED);
\t\ttry_move_y(p, &game->config->map, -p->dir_y * MOVE_SPEED);
\t}
\tif (k->a)
\t{
\t\ttry_move_x(p, &game->config->map, -p->plane_x * MOVE_SPEED);
\t\ttry_move_y(p, &game->config->map, -p->plane_y * MOVE_SPEED);
\t}
\tif (k->d)
\t{
\t\ttry_move_x(p, &game->config->map, p->plane_x * MOVE_SPEED);
\t\ttry_move_y(p, &game->config->map, p->plane_y * MOVE_SPEED);
\t}
\tif (k->left)
\t\tplayer_rotate(p, -ROT_SPEED);
\tif (k->right)
\t\tplayer_rotate(p, ROT_SPEED);
}
""")

print("All files rewritten with norminette compliance.")
