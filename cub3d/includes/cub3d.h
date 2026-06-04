/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:17:35 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include "player.h"
# include "graphics.h"
# include "defines.h"
# include "textures.h"
# include "doors.h"
# include "raycasting.h"
# include "parser.h"
# include "doxygen_groups.h"
# include "../minilibx/mlx.h"

/**
 * @def ft_safe_free
 * @brief Free a pointer and set it to NULL in a single statement.
 *
 * The argument is the *address* of the pointer (e.g.,
 * `ft_safe_free((void **)&game->path_north);`). The macro is NULL-safe
 * at both levels: a NULL address or a NULL `*ptr` is a no-op.
 *
 * @param ptr Address of the pointer to free and reset.
 */
# define ft_safe_free(ptr) \
	do { \
		if ((ptr) && *(ptr)) \
		{ \
			free(*(ptr)); \
			*(ptr) = NULL; \
		} \
	} while (0)

/* init.c */
int		ft_init_game(t_game *game, char *map_file);

/* input.c */
int		ft_input_key_press(int keycode, t_game *game);
int		ft_input_key_release(int keycode, t_game *game);
int		ft_input_mouse_move(int x, int y, t_game *game);

/* ft_error.c */
int		ft_error(t_game *game, char *error_msg);
void	ft_free_game(t_game *game);

/* ft_exit_game.c */
int		ft_exit_game(t_game *game);

void	ft_draw_minimap(t_game *game);
int		ft_load_animation(t_game *game, t_sprite *sprite,
			char *base_path, int count);
void	ft_draw_sprites(t_game *game);
int		ft_load_texture(t_game *game, t_texture *tex, char *path);

#endif
