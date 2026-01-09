#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <math.h>

# include "libft.h"
# include "structs.h"
# include "defines.h"
# include "../minilibx/mlx.h"

// init.c
int	init_game(t_game *game);
char    **get_map(void);

// input.c
int     key_press(int keycode, t_game *game);
int     key_release(int keycode, t_game *game);

// player.c
void    move_player(t_player *player);

// graphics.c
void    put_pixel(int x, int y, int color, t_game *game);
void    clear_image(t_game *game);
void    draw_square(int x, int y, int size, int color, t_game *game);
void    draw_map(t_game *game);

// raycast.c
float   distance(float x, float y);
float   fixed_dist(float x1, float y1, float x2, float y2, t_game *game);
bool    touch(float px, float py, t_game *game);
void    draw_line(t_player *player, t_game *game, float start_x, int i);

//ft_error.c
int	ft_error(t_game *game, char *error_msg);
void	ft_free_game(t_game *game);

// ft_exit_game.c
void    ft_exit_game(t_game *game);

#endif