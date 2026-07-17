/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/11 16:00:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "raycaster.h"
#include "graphics.h"
#include <math.h>

static void	ray_init(t_ray *r, t_player *p, int x)
{
	r->camera_x = 2.0 * x / (double)WIN_WIDTH - 1.0;
	r->dir_x = p->dir_x + p->plane_x * r->camera_x;
	r->dir_y = p->dir_y + p->plane_y * r->camera_x;
	r->map_x = (int)p->x;
	r->map_y = (int)p->y;
	if (fabs(r->dir_x) < 1e-9)
		r->delta_dist_x = 1e30;
	else
		r->delta_dist_x = fabs(1.0 / r->dir_x);
	if (fabs(r->dir_y) < 1e-9)
		r->delta_dist_y = 1e30;
	else
		r->delta_dist_y = fabs(1.0 / r->dir_y);
}

static void	ray_step(t_ray *r, t_player *p)
{
	if (r->dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (p->x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - p->x) * r->delta_dist_x;
	}
	if (r->dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (p->y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - p->y) * r->delta_dist_y;
	}
}

static int	dda_advance(t_ray *r, t_map *map)
{
	char	cell;

	if (r->side_dist_x < r->side_dist_y)
	{
		r->side_dist_x += r->delta_dist_x;
		r->map_x += r->step_x;
		r->side = 0;
	}
	else
	{
		r->side_dist_y += r->delta_dist_y;
		r->map_y += r->step_y;
		r->side = 1;
	}
	if (r->map_y < 0 || r->map_y >= map->height
		|| r->map_x < 0 || r->map_x >= map->width)
	{
		r->hit_cell = '1';
		return (1);
	}
	cell = map->grid[r->map_y][r->map_x];
	if (!is_barrier(cell))
		return (0);
	r->hit_cell = cell;
	return (1);
}

static void	ray_dda(t_ray *r, t_map *map)
{
	int	hit;

	hit = 0;
	while (!hit)
		hit = dda_advance(r, map);
	if (r->side == 0)
		r->perp_wall_dist = r->side_dist_x - r->delta_dist_x;
	else
		r->perp_wall_dist = r->side_dist_y - r->delta_dist_y;
}

void	ft_raycaster_render(t_game *game)
{
	t_ray	ray;
	int		x;

	ft_raycaster_clear(game);
	x = 0;
	while (x < WIN_WIDTH)
	{
		ray_init(&ray, &game->config->player, x);
		ray_step(&ray, &game->config->player);
		ray_dda(&ray, &game->config->map);
		ft_raycaster_draw_column(game, &ray, x);
		if (game->z_buffer)
			game->z_buffer[x] = ray.perp_wall_dist;
		x++;
	}
}
