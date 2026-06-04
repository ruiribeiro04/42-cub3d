/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_doors_h.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         :+:     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:53:11 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_doors_h.c
 * @brief Door parsing helper functions.
 */

#include "cub3d.h"

/**
 * @ingroup parser
 */
void	ft_free_door_map(t_game *game)
{
	int	y;

	y = 0;
	while (y < game->map_height)
		free(game->door_map[y++]);
	free(game->door_map);
	/**
	 * @ingroup parser
	 */
	game->door_map = NULL;
}

int	ft_alloc_door_grid(t_game *game)
{
	int	y;

	game->door_map = malloc(sizeof(t_door **) * game->map_height);
	if (!game->door_map)
		return (1);
	y = 0;
	while (y < game->map_height)
	{
		game->door_map[y] = ft_calloc(game->map_width, sizeof(t_door *));
		if (!game->door_map[y])
		{
			ft_free_door_map(game);
			return (1);
		}
		y++;
	}
	return (0);
}
