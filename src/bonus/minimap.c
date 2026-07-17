/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 13:25:25 by ruiferna          #+#    #+#             */
/*   Updated: 2026/07/17 17:14:01 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"
#include "graphics.h"

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
	ft_frame_fill_rect(g, r, color);
}

static void	draw_background(t_game *g, int tiles_x, int tiles_y)
{
	t_rect	outer;
	t_rect	inner;
	int		bw;

	bw = MINIMAP_BORDER_THICKNESS;
	outer.x0 = MINIMAP_X - bw;
	outer.y0 = MINIMAP_Y - bw;
	outer.x1 = MINIMAP_X + tiles_x * MINIMAP_TILE + bw - 1;
	outer.y1 = MINIMAP_Y + tiles_y * MINIMAP_TILE + bw - 1;
	ft_frame_fill_rect(g, outer, MINIMAP_BORDER_COLOR);
	inner.x0 = MINIMAP_X;
	inner.y0 = MINIMAP_Y;
	inner.x1 = MINIMAP_X + tiles_x * MINIMAP_TILE - 1;
	inner.y1 = MINIMAP_Y + tiles_y * MINIMAP_TILE - 1;
	ft_frame_fill_rect(g, inner, MINIMAP_BG_COLOR);
}

static int	cell_color(char cell)
{
	if (cell == '1')
		return (MINIMAP_WALL_COLOR);
	if (cell == 'D')
		return (MINIMAP_DOOR_COLOR);
	if (cell == 'O')
		return (MINIMAP_OPEN_COLOR);
	if (cell == ' ')
		return (MINIMAP_VOID_COLOR);
	return (MINIMAP_FLOOR_COLOR);
}

static void	draw_player_marker(t_game *g, t_player *p)
{
	t_rect	sq;
	int		cx;
	int		cy;
	int		i;

	cx = MINIMAP_X + (int)p->x * MINIMAP_TILE + MINIMAP_TILE / 2;
	cy = MINIMAP_Y + (int)p->y * MINIMAP_TILE + MINIMAP_TILE / 2;
	sq.x0 = cx - 2;
	sq.y0 = cy - 2;
	sq.x1 = cx + 2;
	sq.y1 = cy + 2;
	ft_frame_fill_rect(g, sq, MINIMAP_PLAYER_COLOR);
	i = 1;
	while (i < 9)
	{
		ft_frame_put_pixel(g, cx + (int)(p->dir_x * i),
			cy + (int)(p->dir_y * i), MINIMAP_DIR_COLOR);
		i++;
	}
}

void	ft_minimap_draw(t_game *game)
{
	int	x;
	int	y;
	int	max_x;
	int	max_y;

	max_y = game->config->map.height;
	if (max_y > MINIMAP_MAX_TILES_Y)
		max_y = MINIMAP_MAX_TILES_Y;
	max_x = game->config->map.width;
	if (max_x > MINIMAP_MAX_TILES_X)
		max_x = MINIMAP_MAX_TILES_X;
	draw_background(game, max_x, max_y);
	y = 0;
	while (y < max_y)
	{
		x = 0;
		while (x < max_x)
		{
			draw_tile(game, x, y, cell_color(game->config->map.grid[y][x]));
			x++;
		}
		y++;
	}
	draw_player_marker(game, &game->config->player);
}
