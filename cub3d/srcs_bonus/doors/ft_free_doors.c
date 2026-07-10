/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_doors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:20:47 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_free_doors.c
 * @brief Free door resources on exit.
 */

#include "cub3d.h"

/**
 * @ingroup graphics
 */
void	ft_free_doors(t_game *game)
{
	int	y;

	if (game->doors)
	{
		if (game->doors[0].tex.img && game->mlx)
			mlx_destroy_image(game->mlx, game->doors[0].tex.img);
		free(game->doors);
		game->doors = NULL;
	}
	if (game->door_map)
	{
		y = 0;
		while (y < game->map_height)
		{
			free(game->door_map[y]);
			y++;
		}
		free(game->door_map);
		game->door_map = NULL;
	}
}
