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

void	ft_frame_put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = game->frame.data + (y * game->frame.line_len
			+ x * (game->frame.bpp / 8));
	*(int *)dst = color;
}

void	ft_frame_fill_rect(t_game *game, t_rect rect, int color)
{
	int	x;
	int	y;

	y = rect.y0;
	while (y <= rect.y1)
	{
		x = rect.x0;
		while (x <= rect.x1)
		{
			ft_frame_put_pixel(game, x, y, color);
			x++;
		}
		y++;
	}
}
