/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_clear.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 12:21:47 by ruiferna          #+#    #+#             */
/*   Updated: 2026/07/17 17:24:37 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"
#include "graphics.h"

void	ft_raycaster_clear(t_game *game)
{
	t_rect	top;
	t_rect	bottom;

	top.x0 = 0;
	top.y0 = 0;
	top.x1 = WIN_WIDTH - 1;
	top.y1 = WIN_HEIGHT / 2 - 1;
	bottom.x0 = 0;
	bottom.y0 = WIN_HEIGHT / 2;
	bottom.x1 = WIN_WIDTH - 1;
	bottom.y1 = WIN_HEIGHT - 1;
	ft_frame_fill_rect(game, top, game->ceiling_color);
	ft_frame_fill_rect(game, bottom, game->floor_color);
}

void	ft_draw_solid(t_game *game, t_ray *r, int x, int color)
{
	int	y;

	y = r->draw_start;
	while (y < r->draw_end)
	{
		ft_frame_put_pixel(game, x, y, color);
		y++;
	}
}
