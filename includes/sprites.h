/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 14:03:50 by ruiferna          #+#    #+#             */
/*   Updated: 2026/07/17 17:09:48 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITES_H
# define SPRITES_H

# include "cub3d.h"

typedef struct s_sprite_draw
{
	int		screen_x;
	int		sprite_height;
	int		sprite_width;
	int		draw_start_y;
	int		draw_end_y;
	int		draw_start_x;
	int		draw_end_x;
}			t_sprite_draw;

typedef struct s_stripe_ctx
{
	t_game			*g;
	t_sprite_draw	*d;
	int				stripe;
	int				tex_x;
	double			ty;
}			t_stripe_ctx;

void	sprites_render(t_game *game);
void	draw_sprite_stripes(t_game *g, t_sprite_draw *d, double ty);
void	sprites_update(t_game *game);
void	sprites_sort(t_game *game);
int		sprites_init(t_game *game);

#endif
