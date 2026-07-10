/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:52:34 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_free.c
 * @brief Parser memory cleanup functions for paths and map grid.
 */

#include "cub3d.h"

/**
 * @ingroup parser
 */
void	ft_free_parser_paths(t_game *game)
{
	ft_safe_free((void **)&game->path_north);
	ft_safe_free((void **)&game->path_south);
	ft_safe_free((void **)&game->path_east);
	ft_safe_free((void **)&game->path_west);
}

void	ft_free_parser_map(t_game *game)
{
	int	i;

	if (!game->map)
		return ;
	i = 0;
	while (game->map[i])
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
	game->map = NULL;
	game->map_width = 0;
	game->map_height = 0;
}
