/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/11 16:00:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GRAPHICS_H
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
int		load_texture(t_game *game, t_texture *tex, char *path);
void	destroy_texture(t_game *game, t_texture *tex);
int		free_sprite_frames(t_game *game, int count);
int		color_to_int(t_color c, int endian);
int		hook_key_press(int keycode, t_game *game);
int		hook_key_release(int keycode, t_game *game);
int		hook_exit(t_game *game);
int		hook_loop(t_game *game);
void	player_update(t_game *game);
void	raycaster_render(t_game *game);
void	player_init_direction(t_player *p);
int		init_sprites_if_present(t_game *game, t_config *cfg);
int		init_optional_textures(t_game *game, t_config *cfg);

# define KEY_ESC   65307
# define KEY_W     119
# define KEY_A     97
# define KEY_S     115
# define KEY_D     100
# define KEY_LEFT  65361
# define KEY_RIGHT 65363
# define KEY_E     101

#endif
