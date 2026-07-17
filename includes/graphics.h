/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 19:03:01 by ruiferna          #+#    #+#             */
/*   Updated: 2026/07/17 17:17:22 by vde-maga         ###   ########.fr       */
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

void	ft_frame_put_pixel(t_game *game, int x, int y, int color);
void	ft_frame_fill_rect(t_game *game, t_rect rect, int color);
int		ft_load_texture(t_game *game, t_texture *tex, char *path);
void	ft_destroy_texture(t_game *game, t_texture *tex);
int		ft_free_sprite_frames(t_game *game, int count);
int		ft_color_to_int(t_color c, int endian);
int		ft_hook_key_press(int keycode, t_game *game);
int		ft_hook_key_release(int keycode, t_game *game);
int		ft_hook_exit(t_game *game);
int		ft_hook_loop(t_game *game);
int		ft_init_sprites_if_present(t_game *game, t_config *cfg);
int		ft_init_optional_textures(t_game *game, t_config *cfg);

# define KEY_ESC   65307
# define KEY_W     119
# define KEY_A     97
# define KEY_S     115
# define KEY_D     100
# define KEY_LEFT  65361
# define KEY_RIGHT 65363
# define KEY_E     101

#endif
