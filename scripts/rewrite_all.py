#!/usr/bin/env python3
"""
Master rewrite script for cub3D — implements all 7 user requests:
1. Remove global var (use mlx_loop_end)
2. Fix doors + sprites (DDA stops on D, door texture, sprite rendering)
3. Makefile: make=mandatory, make bonus=separate compile
4. Multiple sprite files (sprite01.xpm, sprite02.xpm...)
5. Mouse locked to window (mlx_mouse_move + mlx_mouse_hide)
6. Minimap triangle player indicator
7. Door E key only when adjacent
"""

import os

ROOT = '/home/z/my-project/cub3d'

def h(name):
    """Generate 80-char 42 header."""
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
#  includes/cub3d.h
# =====================================================================
w(f'{ROOT}/includes/cub3d.h', h('cub3d.h') + r"""#ifndef CUB3D_H
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
# define MAX_SPRITE_FRAMES 10
# define SPRITE_ANIM_DELAY 15
# define MOUSE_SENS 0.002

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}			t_color;

typedef struct s_texture_paths
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}			t_texture_paths;

typedef struct s_player
{
	double	x;
	double	y;
	char	direction;
	double	angle;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}			t_player;

typedef struct s_map
{
	char	**grid;
	int		height;
	int		width;
}			t_map;

typedef struct s_sprite
{
	double	x;
	double	y;
	double	distance;
}			t_sprite;

typedef struct s_config
{
	t_texture_paths	textures;
	t_color			floor;
	t_color			ceiling;
	t_map			map;
	t_player		player;
	int				has_north;
	int				has_south;
	int				has_west;
	int				has_east;
	int				has_floor;
	int				has_ceiling;
	int				has_player;
	char			*sprite_texture;
	int				has_sprite;
	char			*door_texture;
	int				has_door_texture;
	t_sprite		*sprite_positions;
	int				num_sprites;
}			t_config;

typedef struct s_img
{
	void	*ptr;
	char	*data;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}			t_img;

typedef struct s_texture
{
	t_img	img;
	int		*pixels;
}			t_texture;

typedef struct s_keys
{
	int		w;
	int		a;
	int		s;
	int		d;
	int		left;
	int		right;
}			t_keys;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	t_img			frame;
	t_config		*config;
	t_texture		tex[4];
	t_texture		door_tex;
	int				has_door_tex;
	int				floor_color;
	int				ceiling_color;
	t_keys			keys;
	t_sprite		*sprites;
	int				num_sprites;
	t_texture		*sprite_frames;
	int				num_sprite_frames;
	int				sprite_frame;
	int				sprite_anim_counter;
	int				has_sprites;
	double			*z_buffer;
}			t_game;

# define TEX_NORTH 0
# define TEX_SOUTH 1
# define TEX_WEST  2
# define TEX_EAST  3

t_config		*parse_cub_file(const char *path);
void			free_config(t_config *config);
void			cub_error(const char *msg);
void			*cub_error_ret(const char *msg, void *ret);
int				cub_error_int(const char *msg);
int				game_init(t_game *game, t_config *config);
void			game_cleanup(t_game *game);
int				game_run(t_game *game);

#endif
""")

# =====================================================================
#  src/main.c — NO GLOBAL, clean exit with mlx_loop_end
# =====================================================================
w(f'{ROOT}/src/main.c', h('main.c') + r"""#include "cub3d.h"
#include "graphics/graphics.h"
#include "player/player.h"
#include <stdlib.h>
#include <libft.h>

static int	validate_args(int argc, char **argv)
{
	(void)argv;
	if (argc != 2)
		return (cub_error_int("Usage: ./cub3D <map.cub>"));
	return (0);
}

int	main(int argc, char **argv)
{
	t_config	*config;
	t_game		game;

	if (validate_args(argc, argv) < 0)
		return (1);
	config = parse_cub_file(argv[1]);
	if (!config)
		return (1);
	player_init_direction(&config->player);
	ft_memset(&game, 0, sizeof(t_game));
	game.config = config;
	if (game_init(&game, config) < 0)
	{
		game_cleanup(&game);
		free_config(config);
		return (1);
	}
	game_run(&game);
	game_cleanup(&game);
	free_config(config);
	return (0);
}
""")

# =====================================================================
#  src/graphics/graphics.h
# =====================================================================
w(f'{ROOT}/src/graphics/graphics.h', h('graphics.h') + r"""#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "cub3d.h"

typedef struct s_rect
{
	int		x0;
	int		y0;
	int		x1;
	int		y1;
}			t_rect;

void	frame_put_pixel(t_game *game, int x, int y, int color);
void	frame_fill_rect(t_game *game, t_rect rect, int color);
void	frame_clear(t_game *game);
int		load_texture(t_game *game, t_texture *tex, char *path);
void	destroy_texture(t_game *game, t_texture *tex);
int		color_to_int(t_color c);
int		hook_key_press(int keycode, t_game *game);
int		hook_key_release(int keycode, t_game *game);
int		hook_exit(t_game *game);
int		hook_loop(t_game *game);
void	player_update(t_game *game);
void	raycaster_render(t_game *game);
void	player_init_direction(t_player *p);
int		init_sprites_if_present(t_game *game, t_config *cfg);

# define KEY_ESC   65307
# define KEY_W     119
# define KEY_A     97
# define KEY_S     115
# define KEY_D     100
# define KEY_LEFT  65361
# define KEY_RIGHT 65363
# define KEY_E     101

#endif
""")

# =====================================================================
#  src/graphics/hooks_common.c — shared hook functions (2 funcs)
# =====================================================================
w(f'{ROOT}/src/graphics/hooks_common.c', h('hooks_common.c') + r"""#include "graphics.h"

int	hook_key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys.w = 0;
	if (keycode == KEY_A)
		game->keys.a = 0;
	if (keycode == KEY_S)
		game->keys.s = 0;
	if (keycode == KEY_D)
		game->keys.d = 0;
	if (keycode == KEY_LEFT)
		game->keys.left = 0;
	if (keycode == KEY_RIGHT)
		game->keys.right = 0;
	return (0);
}

int	hook_exit(t_game *game)
{
	mlx_loop_end(game->mlx);
	return (0);
}
""")

# =====================================================================
#  src/graphics/hooks.c — MANDATORY hook_key_press + hook_loop (2 funcs)
# =====================================================================
w(f'{ROOT}/src/graphics/hooks.c', h('hooks.c') + r"""#include "graphics.h"

int	hook_key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		mlx_loop_end(game->mlx);
		return (0);
	}
	if (keycode == KEY_W)
		game->keys.w = 1;
	if (keycode == KEY_A)
		game->keys.a = 1;
	if (keycode == KEY_S)
		game->keys.s = 1;
	if (keycode == KEY_D)
		game->keys.d = 1;
	if (keycode == KEY_LEFT)
		game->keys.left = 1;
	if (keycode == KEY_RIGHT)
		game->keys.right = 1;
	return (0);
}

int	hook_loop(t_game *game)
{
	player_update(game);
	raycaster_render(game);
	mlx_put_image_to_window(game->mlx, game->win,
		game->frame.ptr, 0, 0);
	return (0);
}
""")

# =====================================================================
#  src/graphics/hooks_bonus.c — BONUS hook_key_press + hook_loop
# =====================================================================
w(f'{ROOT}/src/graphics/hooks_bonus.c', h('hooks_bonus.c') + r"""#include "graphics.h"
#include "../bonus/bonus.h"

int	hook_key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		mlx_loop_end(game->mlx);
		return (0);
	}
	if (keycode == KEY_W)
		game->keys.w = 1;
	if (keycode == KEY_A)
		game->keys.a = 1;
	if (keycode == KEY_S)
		game->keys.s = 1;
	if (keycode == KEY_D)
		game->keys.d = 1;
	if (keycode == KEY_LEFT)
		game->keys.left = 1;
	if (keycode == KEY_RIGHT)
		game->keys.right = 1;
	if (keycode == KEY_E)
		door_try_front(game);
	return (0);
}

int	hook_loop(t_game *game)
{
	player_update(game);
	raycaster_render(game);
	sprites_update(game);
	sprites_render(game);
	minimap_draw(game);
	mlx_mouse_move(game->mlx, game->win,
		WIN_WIDTH / 2, WIN_HEIGHT / 2);
	mlx_put_image_to_window(game->mlx, game->win,
		game->frame.ptr, 0, 0);
	return (0);
}
""")

# =====================================================================
#  src/graphics/run.c — MANDATORY game_run
# =====================================================================
w(f'{ROOT}/src/graphics/run.c', h('run.c') + r"""#include "graphics.h"

int	game_run(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, hook_key_press, game);
	mlx_hook(game->win, 3, 1L << 1, hook_key_release, game);
	mlx_hook(game->win, 17, 0, hook_exit, game);
	mlx_loop_hook(game->mlx, hook_loop, game);
	mlx_loop(game->mlx);
	return (0);
}
""")

# =====================================================================
#  src/graphics/run_bonus.c — BONUS game_run (mouse hook + hide)
# =====================================================================
w(f'{ROOT}/src/graphics/run_bonus.c', h('run_bonus.c') + r"""#include "graphics.h"
#include "../bonus/bonus.h"

int	game_run(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, hook_key_press, game);
	mlx_hook(game->win, 3, 1L << 1, hook_key_release, game);
	mlx_hook(game->win, 17, 0, hook_exit, game);
	mlx_hook(game->win, 6, 1L << 6, hook_mouse_move, game);
	mlx_mouse_hide(game->mlx, game->win);
	mlx_mouse_move(game->mlx, game->win,
		WIN_WIDTH / 2, WIN_HEIGHT / 2);
	mlx_loop_hook(game->mlx, hook_loop, game);
	mlx_loop(game->mlx);
	return (0);
}
""")

# =====================================================================
#  src/graphics/init.c
# =====================================================================
w(f'{ROOT}/src/graphics/init.c', h('init.c') + r"""#include "graphics.h"
#include <stdlib.h>

int	color_to_int(t_color c)
{
	return ((c.r << 16) | (c.g << 8) | c.b);
}

static void	init_keys(t_keys *keys)
{
	keys->w = 0;
	keys->a = 0;
	keys->s = 0;
	keys->d = 0;
	keys->left = 0;
	keys->right = 0;
}

static int	load_all_textures(t_game *game, t_config *cfg)
{
	if (load_texture(game, &game->tex[TEX_NORTH], cfg->textures.north) < 0)
		return (-1);
	if (load_texture(game, &game->tex[TEX_SOUTH], cfg->textures.south) < 0)
		return (-1);
	if (load_texture(game, &game->tex[TEX_WEST], cfg->textures.west) < 0)
		return (-1);
	if (load_texture(game, &game->tex[TEX_EAST], cfg->textures.east) < 0)
		return (-1);
	return (0);
}

static int	init_frame(t_game *game)
{
	game->frame.ptr = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->frame.ptr)
		return (-1);
	game->frame.data = mlx_get_data_addr(game->frame.ptr,
			&game->frame.bpp, &game->frame.line_len,
			&game->frame.endian);
	if (!game->frame.data)
		return (-1);
	game->frame.width = WIN_WIDTH;
	game->frame.height = WIN_HEIGHT;
	return (0);
}

int	game_init(t_game *game, t_config *config)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (cub_error_int("mlx_init failed"));
	game->win = mlx_new_window(game->mlx, WIN_WIDTH,
			WIN_HEIGHT, "cub3D");
	if (!game->win)
		return (cub_error_int("mlx_new_window failed"));
	if (init_frame(game) < 0)
		return (cub_error_int("Failed to create frame image"));
	game->config = config;
	game->floor_color = color_to_int(config->floor);
	game->ceiling_color = color_to_int(config->ceiling);
	init_keys(&game->keys);
	game->z_buffer = (double *)malloc(sizeof(double) * WIN_WIDTH);
	if (!game->z_buffer)
		return (cub_error_int("Failed to alloc z_buffer"));
	if (load_all_textures(game, config) < 0)
		return (cub_error_int("Failed to load textures"));
	game->has_door_tex = 0;
	if (config->has_door_texture)
	{
		if (load_texture(game, &game->door_tex,
				config->door_texture) < 0)
			return (cub_error_int("Failed to load door texture"));
		game->has_door_tex = 1;
	}
	if (init_sprites_if_present(game, config) < 0)
		return (-1);
	return (0);
}
""")

# =====================================================================
#  src/graphics/cleanup.c
# =====================================================================
w(f'{ROOT}/src/graphics/cleanup.c', h('cleanup.c') + r"""#include "graphics.h"
#include <stdlib.h>

void	destroy_texture(t_game *game, t_texture *tex)
{
	if (tex->pixels)
		free(tex->pixels);
	tex->pixels = NULL;
	if (tex->img.ptr)
		mlx_destroy_image(game->mlx, tex->img.ptr);
	tex->img.ptr = NULL;
}

void	game_cleanup(t_game *game)
{
	int	i;

	if (!game)
		return ;
	if (game->has_sprites)
	{
		i = 0;
		while (i < game->num_sprite_frames)
		{
			destroy_texture(game, &game->sprite_frames[i]);
			i++;
		}
		free(game->sprite_frames);
	}
	if (game->sprites)
		free(game->sprites);
	if (game->has_door_tex)
		destroy_texture(game, &game->door_tex);
	i = 0;
	while (i < 4)
	{
		destroy_texture(game, &game->tex[i]);
		i++;
	}
	if (game->z_buffer)
		free(game->z_buffer);
	if (game->frame.ptr)
		mlx_destroy_image(game->mlx, game->frame.ptr);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
}
""")

# =====================================================================
#  src/graphics/textures.c
# =====================================================================
w(f'{ROOT}/src/graphics/textures.c', h('textures.c') + r"""#include "graphics.h"
#include <stdlib.h>

static int	cache_pixels(t_texture *tex)
{
	int		i;
	int		num_pixels;
	char	*src;

	num_pixels = tex->img.width * tex->img.height;
	tex->pixels = (int *)malloc(sizeof(int) * num_pixels);
	if (!tex->pixels)
		return (-1);
	src = tex->img.data;
	i = 0;
	while (i < num_pixels)
	{
		tex->pixels[i] = *(int *)(src + i * (tex->img.bpp / 8));
		i++;
	}
	return (0);
}

int	load_texture(t_game *game, t_texture *tex, char *path)
{
	tex->img.ptr = mlx_xpm_file_to_image(game->mlx, path,
			&tex->img.width, &tex->img.height);
	if (!tex->img.ptr)
		return (cub_error_int("Failed to load texture file"));
	tex->img.data = mlx_get_data_addr(tex->img.ptr, &tex->img.bpp,
			&tex->img.line_len, &tex->img.endian);
	if (!tex->img.data)
	{
		mlx_destroy_image(game->mlx, tex->img.ptr);
		return (cub_error_int("Failed to get texture data"));
	}
	if (cache_pixels(tex) < 0)
	{
		mlx_destroy_image(game->mlx, tex->img.ptr);
		return (cub_error_int("Failed to cache texture pixels"));
	}
	return (0);
}
""")

# =====================================================================
#  src/graphics/pixel.c
# =====================================================================
w(f'{ROOT}/src/graphics/pixel.c', h('pixel.c') + r"""#include "graphics.h"

void	frame_put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = game->frame.data + (y * game->frame.line_len
			+ x * (game->frame.bpp / 8));
	*(int *)dst = color;
}

void	frame_fill_rect(t_game *game, t_rect rect, int color)
{
	int	x;
	int	y;

	y = rect.y0;
	while (y <= rect.y1)
	{
		x = rect.x0;
		while (x <= rect.x1)
		{
			frame_put_pixel(game, x, y, color);
			x++;
		}
		y++;
	}
}

void	frame_clear(t_game *game)
{
	t_rect	r;

	r.x0 = 0;
	r.y0 = 0;
	r.x1 = WIN_WIDTH - 1;
	r.y1 = WIN_HEIGHT - 1;
	frame_fill_rect(game, r, 0);
}
""")

# =====================================================================
#  src/graphics/init_sprites.c — load multiple sprite frames
# =====================================================================
w(f'{ROOT}/src/graphics/init_sprites.c', h('init_sprites.c') + r"""#include "graphics.h"
#include "../bonus/sprites.h"
#include <stdlib.h>
#include <libft.h>

/* Builds path: base + "01.xpm" etc. */
static void	build_path(char *dst, size_t size,
					const char *base, int num)
{
	char	num_str[3];

	ft_strlcpy(dst, base, size);
	if (num < 10)
	{
		num_str[0] = '0';
		num_str[1] = '0' + num;
	}
	else
	{
		num_str[0] = '0' + (num / 10);
		num_str[1] = '0' + (num % 10);
	}
	num_str[2] = '\0';
	ft_strlcat(dst, num_str, size);
	ft_strlcat(dst, ".xpm", size);
}

/* Loads all sprite frames (sprite01.xpm, sprite02.xpm...). */
static int	load_sprite_frames(t_game *game, t_config *cfg)
{
	char	path[256];
	int		i;

	game->sprite_frames = (t_texture *)malloc(
			sizeof(t_texture) * MAX_SPRITE_FRAMES);
	if (!game->sprite_frames)
		return (cub_error_int("Failed to alloc sprite frames"));
	i = 0;
	while (i < MAX_SPRITE_FRAMES)
	{
		build_path(path, sizeof(path), cfg->sprite_texture, i + 1);
		if (load_texture(game, &game->sprite_frames[i], path) < 0)
			break ;
		i++;
	}
	game->num_sprite_frames = i;
	if (i == 0)
		return (cub_error_int("No sprite frames found"));
	return (0);
}

int	init_sprites_if_present(t_game *game, t_config *cfg)
{
	if (!cfg->has_sprite)
		return (0);
	if (load_sprite_frames(game, cfg) < 0)
		return (-1);
	if (sprites_init(game) < 0)
		return (-1);
	return (0);
}
""")

print("=== Part 1 done (graphics + main) ===")
