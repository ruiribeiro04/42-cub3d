/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sprite_collect.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/11 16:00:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser_internal.h"
#include <stdlib.h>
#include <libft.h>

static int	count_sprites(t_config *cfg)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (y < cfg->map.height)
	{
		x = 0;
		while (x < cfg->map.width)
		{
			if (cfg->map.grid[y][x] == '2')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static int	alloc_sprite_positions(t_config *cfg)
{
	cfg->sprite_positions = (t_sprite *)malloc(
			sizeof(t_sprite) * cfg->num_sprites);
	if (!cfg->sprite_positions)
	{
		cub_error("Failed to alloc sprite positions");
		cfg->num_sprites = 0;
		return (-1);
	}
	return (0);
}

static void	collect_row(t_config *cfg, int y, int *idx)
{
	int	x;

	x = 0;
	while (x < cfg->map.width)
	{
		if (cfg->map.grid[y][x] == '2')
		{
			cfg->sprite_positions[*idx].x = (double)x + 0.5;
			cfg->sprite_positions[*idx].y = (double)y + 0.5;
			cfg->sprite_positions[*idx].distance = 0.0;
			cfg->map.grid[y][x] = '0';
			(*idx)++;
		}
		x++;
	}
}

void	convert_sprites_to_floor(t_config *cfg)
{
	int	y;
	int	idx;

	cfg->num_sprites = 0;
	cfg->sprite_positions = NULL;
	if (!cfg->has_sprite)
		return ;
	cfg->num_sprites = count_sprites(cfg);
	if (cfg->num_sprites == 0)
		return ;
	if (alloc_sprite_positions(cfg) < 0)
		return ;
	idx = 0;
	y = 0;
	while (y < cfg->map.height)
	{
		collect_row(cfg, y, &idx);
		y++;
	}
}
