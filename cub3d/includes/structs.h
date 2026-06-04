/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:18:46 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_door_state
{
	DOOR_CLOSED,
	DOOR_OPENING,
	DOOR_OPEN,
	DOOR_CLOSING
}					t_door_state;

typedef struct s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct s_player
{
	float			x;
	float			y;
	float			angle;
	bool			key_up;
	bool			key_down;
	bool			key_left;
	bool			key_right;
	bool			left_rotate;
	bool			right_rotate;
}					t_player;

typedef struct s_texture
{
	void			*img;
	char			*data;
	int				width;
	int				height;
	int				bpp;
	int				size_line;
	int				endian;
}					t_texture;

typedef struct s_door
{
	int				x;
	int				y;
	t_door_state	state;
	float			progress;
	t_texture		tex;
}					t_door;

typedef struct s_sprite
{
	float			x;
	float			y;
	t_texture		*frames;
	int				frame_count;
	int				current_frame;
	double			anim_time;
	float			distance;
}					t_sprite;

typedef struct s_ray
{
	float			dir_x;
	float			dir_y;
	float			delta_x;
	float			delta_y;
	float			side_x;
	float			side_y;
	float			perp_dist;
	int				step_x;
	int				step_y;
	int				map_x;
	int				map_y;
	int				side;
	int				wall_height;
	int				draw_start;
	int				draw_end;
	float			wall_x;
	int				tex_x;
	t_door			*hit_door;
}					t_ray;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*data;
	int				bpp;
	int				size_line;
	int				endian;
	int				map_width;
	int				map_height;
	t_player		player;
	t_ray			ray;
	char			**map;
	t_texture		tex_north;
	t_texture		tex_south;
	t_texture		tex_east;
	t_texture		tex_west;
	char			*path_north;
	char			*path_south;
	char			*path_east;
	char			*path_west;
	int				floor_color;
	int				ceiling_color;
	int				floor_color_set;
	int				ceiling_color_set;
	t_sprite		*sprites;
	int				sprite_count;
	double			*z_buffer;
	struct timeval	last_time;
	t_door			*doors;
	int				door_count;
	t_door			***door_map;
	bool			error_flag;
}					t_game;

#endif
