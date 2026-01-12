#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <math.h>
#include <fcntl.h>

# include "libft.h"
# include "structs.h"
# include "graphics.h"
# include "defines.h"
# include "raycasting.h"
# include "../minilibx/mlx.h"

// init.c
int	ft_init_game(t_game *game);
char    **ft_get_map(void);

// input.c
int     ft_input_key_press(int keycode, t_game *game);
int     ft_input_key_release(int keycode, t_game *game);

// player.c
void    ft_player_move_player(t_player *player);

//ft_error.c
int	ft_error(t_game *game, char *error_msg);
void	ft_free_game(t_game *game);

// ft_exit_game.c
void    ft_exit_game(t_game *game);

#endif