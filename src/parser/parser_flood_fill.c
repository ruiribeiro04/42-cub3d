/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_flood_fill.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/15 16:00:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser_internal.h"
#include <stdlib.h>
#include <libft.h>


static int	explore(t_flood_ctx *ctx, int x, int y)
{
	int	idx;
	int	cell;

	if (!ft_map_in_bounds(&ctx->cfg->map, x, y))
		return (-1);
	idx = y * ctx->cfg->map.width + x;
	if (ctx->visited[idx])
		return (0);
	cell = ctx->cfg->map.grid[y][x];
	if (cell == '1')
		return (0);
	ctx->visited[idx] = 1;
	ctx->queue[ctx->q_tail++] = idx;
	return (0);
}

static int	process_queue(t_flood_ctx *ctx, int q_head,
								t_config *cfg)
{
	int	idx;
	int	x;
	int	y;

	while (q_head < ctx->q_tail)
	{
		idx = ctx->queue[q_head++];
		x = idx % cfg->map.width;
		y = idx / cfg->map.width;
		if (explore(ctx, x + 1, y) < 0
			|| explore(ctx, x - 1, y) < 0
			|| explore(ctx, x, y + 1) < 0
			|| explore(ctx, x, y - 1) < 0)
			return (-1);
	}
	return (0);
}

static int	flood_fill_iter(t_config *cfg, char *visited,
							int sx, int sy)
{
	t_flood_ctx	ctx;
	int			q_head;
	int			idx;
	int			map_size;

	map_size = cfg->map.height * cfg->map.width;
	ctx.cfg = cfg;
	ctx.visited = visited;
	ctx.q_tail = 0;
	ctx.queue = (int *)malloc(sizeof(int) * (size_t)map_size);
	if (!ctx.queue)
		return (-1);
	q_head = 0;
	idx = sy * cfg->map.width + sx;
	ctx.queue[ctx.q_tail++] = idx;
	visited[idx] = 1;
	if (process_queue(&ctx, q_head, cfg) < 0)
	{
		free(ctx.queue);
		return (-1);
	}
	free(ctx.queue);
	return (0);
}

int	ft_flood_fill_check(t_config *cfg)
{
	char	*visited;
	int		result;
	long	map_size;

	map_size = (long)cfg->map.height * (long)cfg->map.width;
	if (map_size <= 0 || map_size > MAP_MAX_CELLS)
		return (ft_cub_error_int("Map dimensions out of range"));
	visited = (char *)malloc((size_t)map_size);
	if (!visited)
		return (ft_cub_error_int("Memory allocation failed"));
	ft_bzero(visited, (size_t)map_size);
	result = flood_fill_iter(cfg, visited,
			(int)cfg->player.x, (int)cfg->player.y);
	free(visited);
	if (result < 0)
		return (ft_cub_error_int("Map is not closed (player can escape)"));
	return (0);
}
