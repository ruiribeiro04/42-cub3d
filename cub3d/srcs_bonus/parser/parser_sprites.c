/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:21:58 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_sprites(t_game *game)
{
	int	y;
	int	x;
	int	count;

	count = 0;
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'A' || game->map[y][x] == '2')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static void	store_sprite_pos(t_game *game, int index, int x, int y)
{
	game->sprites[index].x = (x + 0.5) * BLOCK;
	game->sprites[index].y = (y + 0.5) * BLOCK;
	game->sprites[index].frames = NULL;
	game->sprites[index].frame_count = 0;
	game->sprites[index].current_frame = 0;
	game->sprites[index].anim_time = 0.0;
	game->sprites[index].distance = 0.0;
	game->map[y][x] = '0';
}

int	ft_extract_sprites(t_game *game)
{
	int	y;
	int	x;
	int	i;

	game->sprite_count = count_sprites(game);
	if (game->sprite_count == 0)
		return (0);
	game->sprites = malloc(sizeof(t_sprite) * game->sprite_count);
	if (!game->sprites)
		return (1);
	i = 0;
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'A' || game->map[y][x] == '2')
				store_sprite_pos(game, i++, x, y);
			x++;
		}
		y++;
	}
	return (0);
}

void	ft_free_parsed_sprites(t_game *game)
{
	if (game->sprites)
	{
		free(game->sprites);
		game->sprites = NULL;
	}
	game->sprite_count = 0;
}
