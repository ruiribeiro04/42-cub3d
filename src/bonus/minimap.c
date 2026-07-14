/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/11 16:00:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "bonus.h"
#include "../graphics/graphics.h"

static void	draw_tile(t_game *g, int mx, int my, int color)
{
	t_rect	r;
	int		sx;
	int		sy;

	sx = MINIMAP_X + mx * MINIMAP_TILE;
	sy = MINIMAP_Y + my * MINIMAP_TILE;
	r.x0 = sx;
	r.y0 = sy;
	r.x1 = sx + MINIMAP_TILE - 1;
	r.y1 = sy + MINIMAP_TILE - 1;
	frame_fill_rect(g, r, color);
}

static void	draw_player_dir_line(t_game *g, t_player *p,
									int cx, int cy)
{
	int	i;
	int	px;
	int	py;

	i = 0;
	while (i < 6)
	{
		px = cx + (int)(p->dir_x * i);
		py = cy + (int)(p->dir_y * i);
		frame_put_pixel(g, px, py, 0x00FFFF00);
		frame_put_pixel(g, px + 1, py, 0x00FFFF00);
		frame_put_pixel(g, px, py + 1, 0x00FFFF00);
		i++;
	}
}

static void	draw_player_marker(t_game *g)
{
	t_player	*p;
	int			cx;
	int			cy;

	p = &g->config->player;
	cx = MINIMAP_X + (int)(p->x * MINIMAP_TILE) + MINIMAP_TILE / 2;
	cy = MINIMAP_Y + (int)(p->y * MINIMAP_TILE) + MINIMAP_TILE / 2;
	frame_put_pixel(g, cx, cy, 0x00FF0000);
	frame_put_pixel(g, cx + 1, cy, 0x00FF0000);
	frame_put_pixel(g, cx - 1, cy, 0x00FF0000);
	frame_put_pixel(g, cx, cy + 1, 0x00FF0000);
	frame_put_pixel(g, cx, cy - 1, 0x00FF0000);
	draw_player_dir_line(g, p, cx, cy);
}

static int	cell_color(char cell)
{
	if (cell == '1')
		return (0x00FFFFFF);
	if (cell == 'D')
		return (0x00AA6600);
	if (cell == 'O')
		return (0x0000AA00);
	return (0x00444444);
}

void	minimap_draw(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->config->map.height)
	{
		x = 0;
		while (x < game->config->map.width)
		{
			draw_tile(game, x, y,
				cell_color(game->config->map.grid[y][x]));
			x++;
		}
		y++;
	}
	draw_player_marker(game);
}
