#!/usr/bin/env python3
"""
Generate ALL graphics/raycaster/player files for Tasks 3-5.
Produces norminette-compliant C with proper 80-char headers and tabs.
"""

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
#  includes/cub3d.h — EXTENDED with graphics types
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

/* An image buffer (off-screen or texture). */
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

/* A texture with its pixel data cached as int array. */
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

/* Main game state. */
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

/* Texture indices in the tex[4] array. */
# define TEX_NORTH 0
# define TEX_SOUTH 1
# define TEX_WEST  2
# define TEX_EAST  3

/* Parser API */
t_config\t\t*parse_cub_file(const char *path);
void\t\tfree_config(t_config *config);
void\t\tcub_error(const char *msg);
void\t\t*cub_error_ret(const char *msg, void *ret);
int\t\t\tcub_error_int(const char *msg);

/* Game lifecycle */
int\t\t\tgame_init(t_game *game, t_config *config);
void\t\tgame_cleanup(t_game *game);
int\t\t\tgame_run(t_game *game);

#endif
""")

# ============================================================================
#  src/graphics/graphics.h — internal graphics API
# ============================================================================
w(f'{ROOT}/src/graphics/graphics.h', header('graphics.h') + """
#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "cub3d.h"

/* Pixel operations on the frame buffer */
void\tframe_put_pixel(t_game *game, int x, int y, int color);
void\tframe_fill_rect(t_game *game, int x0, int y0, int x1, int y1,
\t\t\t\t\tint color);
void\tframe_clear(t_game *game);

/* Texture helpers */
int\t\t\tload_texture(t_game *game, t_texture *tex, char *path);
void\t\tdestroy_texture(t_game *game, t_texture *tex);
int\t\t\tcolor_to_int(t_color c);

/* Hooks callbacks */
int\t\thook_key_press(int keycode, t_game *game);
int\t\thook_key_release(int keycode, t_game *game);
int\t\thook_exit(t_game *game);
int\t\thook_loop(t_game *game);

/* Linux keycodes */
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
#  src/graphics/init.c — game_init (4 functions)
# ============================================================================
w(f'{ROOT}/src/graphics/init.c', header('init.c') + """
#include "graphics.h"
#include <stdlib.h>

/* Converts an RGB t_color to a single int (0x00RRGGBB). */
int\tcolor_to_int(t_color c)
{
\treturn ((c.r << 16) | (c.g << 8) | c.b);
}

/* Initializes the keys struct to all-released. */
static void\tinit_keys(t_keys *keys)
{
\tkeys->w = 0;
\tkeys->a = 0;
\tkeys->s = 0;
\tkeys->d = 0;
\tkeys->left = 0;
\tkeys->right = 0;
}

/* Loads the four wall textures from the config paths. */
static int\tload_all_textures(t_game *game, t_config *cfg)
{
\tif (load_texture(game, &game->tex[TEX_NORTH], cfg->textures.north) < 0)
\t\treturn (-1);
\tif (load_texture(game, &game->tex[TEX_SOUTH], cfg->textures.south) < 0)
\t\treturn (-1);
\tif (load_texture(game, &game->tex[TEX_WEST], cfg->textures.west) < 0)
\t\treturn (-1);
\tif (load_texture(game, &game->tex[TEX_EAST], cfg->textures.east) < 0)
\t\treturn (-1);
\treturn (0);
}

/* Initializes the off-screen frame buffer image. */
static int\tinit_frame(t_game *game)
{
\tgame->frame.ptr = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
\tif (!game->frame.ptr)
\t\treturn (-1);
\tgame->frame.data = mlx_get_data_addr(game->frame.ptr,
\t\t\t&game->frame.bpp, &game->frame.line_len, &game->frame.endian);
\tif (!game->frame.data)
\t\treturn (-1);
\tgame->frame.width = WIN_WIDTH;
\tgame->frame.height = WIN_HEIGHT;
\treturn (0);
}

/* Initializes the entire game: mlx, window, frame, textures. */
int\tgame_init(t_game *game, t_config *config)
{
\tgame->mlx = mlx_init();
\tif (!game->mlx)
\t\treturn (cub_error_int("mlx_init failed"));
\tgame->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
\tif (!game->win)
\t\treturn (cub_error_int("mlx_new_window failed"));
\tif (init_frame(game) < 0)
\t\treturn (cub_error_int("Failed to create frame image"));
\tgame->config = config;
\tgame->floor_color = color_to_int(config->floor);
\tgame->ceiling_color = color_to_int(config->ceiling);
\tinit_keys(&game->keys);
\tif (load_all_textures(game, config) < 0)
\t\treturn (cub_error_int("Failed to load textures"));
\treturn (0);
}
""")

# ============================================================================
#  src/graphics/cleanup.c — game_cleanup + texture destroy (2 funcs)
# ============================================================================
w(f'{ROOT}/src/graphics/cleanup.c', header('cleanup.c') + """
#include "graphics.h"
#include <stdlib.h>

/* Destroys a single texture (image + pixel array). */
void\tdestroy_texture(t_game *game, t_texture *tex)
{
\tif (tex->pixels)
\t\tfree(tex->pixels);
\ttex->pixels = NULL;
\tif (tex->img.ptr)
\t\tmlx_destroy_image(game->mlx, tex->img.ptr);
\ttex->img.ptr = NULL;
}

/* Destroys all resources owned by the game. */
void\tgame_cleanup(t_game *game)
{
\tint\ti;

\tif (!game)
\t\treturn ;
\ti = 0;
\twhile (i < 4)
\t{
\t\tdestroy_texture(game, &game->tex[i]);
\t\ti++;
\t}
\tif (game->frame.ptr)
\t\tmlx_destroy_image(game->mlx, game->frame.ptr);
\tif (game->win)
\t\tmlx_destroy_window(game->mlx, game->win);
\tif (game->mlx)
\t\tmlx_destroy_display(game->mlx);
}
""")

# ============================================================================
#  src/graphics/textures.c — load_texture (2 functions)
# ============================================================================
w(f'{ROOT}/src/graphics/textures.c', header('textures.c') + """
#include "graphics.h"
#include <stdlib.h>
#include <libft.h>

/* Copies the image data into a fast int-pixel array. */
static int\tcache_pixels(t_texture *tex)
{
\tint\t\ti;
\tint\t\tnum_pixels;
\tchar\t*src;

\tnum_pixels = tex->img.width * tex->img.height;
\ttex->pixels = (int *)malloc(sizeof(int) * num_pixels);
\tif (!tex->pixels)
\t\treturn (-1);
\tsrc = tex->img.data;
\ti = 0;
\twhile (i < num_pixels)
\t{
\t\ttex->pixels[i] = *(int *)(src + i * (tex->img.bpp / 8));
\t\ti++;
\t}
\treturn (0);
}

/* Loads an XPM texture file into a t_texture. Returns 0/-1. */
int\tload_texture(t_game *game, t_texture *tex, char *path)
{
\ttex->img.ptr = mlx_xpm_file_to_image(game->mlx, path,
\t\t\t&tex->img.width, &tex->img.height);
\tif (!tex->img.ptr)
\t\treturn (cub_error_int("Failed to load texture file"));
\ttex->img.data = mlx_get_data_addr(tex->img.ptr, &tex->img.bpp,
\t\t\t&tex->img.line_len, &tex->img.endian);
\tif (!tex->img.data)
\t{
\t\tmlx_destroy_image(game->mlx, tex->img.ptr);
\t\treturn (cub_error_int("Failed to get texture data"));
\t}
\tif (cache_pixels(tex) < 0)
\t{
\t\tmlx_destroy_image(game->mlx, tex->img.ptr);
\t\treturn (cub_error_int("Failed to cache texture pixels"));
\t}
\treturn (0);
}
""")

# ============================================================================
#  src/graphics/pixel.c — frame_put_pixel + fill_rect + clear (3 funcs)
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

/* Fills a horizontal rectangle with a solid color. */
void\tframe_fill_rect(t_game *game, int x0, int y0, int x1, int y1,
\t\t\t\t\tint color)
{
\tint\tx;
\tint\ty;

\ty = y0;
\twhile (y <= y1)
\t{
\t\tx = x0;
\t\twhile (x <= x1)
\t\t{
\t\t\tframe_put_pixel(game, x, y, color);
\t\t\tx++;
\t\t}
\t\ty++;
\t}
}

/* Clears the entire frame (fills with black). */
void\tframe_clear(t_game *game)
{
\tframe_fill_rect(game, 0, 0, WIN_WIDTH - 1, WIN_HEIGHT - 1, 0);
}
""")

# ============================================================================
#  src/graphics/hooks.c — key press/release/exit/loop (4 funcs)
# ============================================================================
w(f'{ROOT}/src/graphics/hooks.c', header('hooks.c') + """
#include "graphics.h"
#include <stdlib.h>

/* Sets the corresponding key flag to 1 on key press. */
int\thook_key_press(int keycode, t_game *game)
{
\tif (keycode == KEY_ESC)
\t\texit(0);
\tif (keycode == KEY_W)
\t\tgame->keys.w = 1;
\tif (keycode == KEY_A)
\t\tgame->keys.a = 1;
\tif (keycode == KEY_S)
\t\tgame->keys.s = 1;
\tif (keycode == KEY_D)
\t\tgame->keys.d = 1;
\tif (keycode == KEY_LEFT)
\t\tgame->keys.left = 1;
\tif (keycode == KEY_RIGHT)
\t\tgame->keys.right = 1;
\treturn (0);
}

/* Sets the corresponding key flag to 0 on key release. */
int\thook_key_release(int keycode, t_game *game)
{
\tif (keycode == KEY_W)
\t\tgame->keys.w = 0;
\tif (keycode == KEY_A)
\t\tgame->keys.a = 0;
\tif (keycode == KEY_S)
\t\tgame->keys.s = 0;
\tif (keycode == KEY_D)
\t\tgame->keys.d = 0;
\tif (keycode == KEY_LEFT)
\t\tgame->keys.left = 0;
\tif (keycode == KEY_RIGHT)
\t\tgame->keys.right = 0;
\treturn (0);
}

/* Handles the window close (red cross). */
int\thook_exit(t_game *game)
{
\t(void)game;
\texit(0);
\treturn (0);
}

/* Main loop: process movement, render, push to screen. */
int\thook_loop(t_game *game)
{
\tplayer_update(game);
\traycaster_render(game);
\tmlx_put_image_to_window(game->mlx, game->win, game->frame.ptr, 0, 0);
\treturn (0);
}
""")

print("Graphics files generated.")
