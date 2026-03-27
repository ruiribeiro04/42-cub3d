#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/time.h>

# include "libft.h"
# include "structs.h"
# include "sprites.h"
# include "graphics.h"
# include "defines.h"
# include "textures.h"
# include "raycasting.h"
# include "parser.h"
# include "../minilibx/mlx.h"

// init.c
int		ft_init_game(t_game *game, char *map_file);

// input.c
int		ft_input_key_press(int keycode, t_game *game);
int		ft_input_key_release(int keycode, t_game *game);
int		ft_input_mouse_move(int x, int y, t_game *game);

// player.c
void	ft_player_move(t_game *game);

//ft_error.c
int		ft_error(t_game *game, char *error_msg);
void	ft_free_game(t_game *game);

// ft_exit_game.c
int		ft_exit_game(t_game *game);

void	ft_draw_minimap(t_game *game);
int		ft_load_animation(t_game *game, t_sprite *sprite,
			char *base_path, int count);
void	ft_draw_sprites(t_game *game);
int		ft_load_texture(t_game *game, t_texture *tex, char *path);

#endif
