/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/11 16:00:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

void	frame_put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = game->frame.data + (y * game->frame.line_len
			+ x * (game->frame.bpp / 8));
	*(int *)dst = color;
}

void	frame_fill_rect(t_game *game, t_rect rect, int color)
{
	int	x;
	int	y;

	y = rect.y0;
	while (y <= rect.y1)
	{
		x = rect.x0;
		while (x <= rect.x1)
		{
			frame_put_pixel(game, x, y, color);
			x++;
		}
		y++;
	}
}

void	frame_clear(t_game *game)
{
	t_rect	r;

	r.x0 = 0;
	r.y0 = 0;
	r.x1 = WIN_WIDTH - 1;
	r.y1 = WIN_HEIGHT - 1;
	frame_fill_rect(game, r, 0);
}
