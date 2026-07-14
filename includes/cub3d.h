/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/11 16:00:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
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

int				path_readable(const char *path);
int				map_in_bounds(const t_map *map, int x, int y);

#endif
