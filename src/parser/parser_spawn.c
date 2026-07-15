/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_spawn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/11 16:00:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser_internal.h"

static int	is_spawn_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	check_spawn_cell(t_config *cfg, int x, int y,
								int *count)
{
	if (!is_spawn_char(cfg->map.grid[y][x]))
		return (0);
	(*count)++;
	if (*count > 1)
		return (cub_error_int("Multiple player spawns"));
	cfg->player.x = (double)x + 0.5;
	cfg->player.y = (double)y + 0.5;
	cfg->player.direction = cfg->map.grid[y][x];
	cfg->map.grid[y][x] = '0';
	return (0);
}

int	find_spawn(t_config *cfg)
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
			if (check_spawn_cell(cfg, x, y, &count) < 0)
				return (-1);
			x++;
		}
		y++;
	}
	if (count == 0)
		return (cub_error_int("No player spawn found"));
	cfg->has_player = 1;
	convert_sprites_to_floor(cfg);
	return (0);
}
