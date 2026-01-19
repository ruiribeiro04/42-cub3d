#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	bool	left_rotate;
	bool	right_rotate;
}	t_player;

typedef struct s_texture
{
	void	*img;
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_texture;


typedef struct s_ray
{
	float	dir_x;
	float	dir_y;
	float	delta_x;
	float	delta_y;
	float	side_x;
	float	side_y;
	float	perp_dist;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
	int		side;
	int		wall_height;
	int		draw_start;
	int		draw_end;
	float	wall_x;
	int		tex_x;
}	t_ray;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
	int			map_width;
	int			map_height;
	t_player	player;
	t_ray		ray;
	char		**map;
	t_texture	tex_north;
	t_texture	tex_south;
	t_texture	tex_east;
	t_texture	tex_west;
}	t_game;

#endif