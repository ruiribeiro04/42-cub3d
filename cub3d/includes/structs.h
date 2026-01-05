#ifndef GAME_H
# define GAME_H

typedef struct s_texture
{
}				t_texture;

typedef struct s_mlx
{
	/*
	ptr_mlx
	win_mlx
	*/
}				t_mlx;

typedef struct s_player
{
	/*
	player position
	*/
}				t_player;

typedef struct s_map
{
	/*
	copia do mapa
	*/
}				t_map;

typedef struct s_game
{
	t_map		map;
	t_player	player;
	t_mlx		mlx;
	t_textures	textures;
}				t_game;

#endif