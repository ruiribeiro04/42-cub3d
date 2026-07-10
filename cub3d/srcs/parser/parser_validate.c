/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:52:13 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_validate.c
 * @brief Validate the parsed map: character set and wall closure.
 */

#include "cub3d.h"

/**
 * @ingroup parser
 */
int	ft_validate_map_chars(t_game *game)
{
	int	y;

	y = 0;
	while (game->map[y])
	{
		if (ft_check_row_chars(game->map, y))
			return (1);
		y++;
	}
	return (0);
}

static void	ft_free_map_copy(char **map_copy)
{
	int	i;

	i = 0;
	while (map_copy[i])
		free(map_copy[i++]);
	free(map_copy);
}

static int	ft_count_height(char **map)
{
	int	h;

	h = 0;
	while (map[h])
		h++;
	return (h);
}

char	**ft_copy_map(t_game *game)
{
	char	**map_copy;
	int		y;
	int		h;

	h = ft_count_height(game->map);
	map_copy = (char **)ft_calloc(h + 1, sizeof(char *));
	if (!map_copy)
		return (NULL);
	y = 0;
	while (y < h)
	{
		map_copy[y] = ft_strdup(game->map[y]);
		if (!map_copy[y])
		{
			while (y > 0)
				free(map_copy[--y]);
			free(map_copy);
			return (NULL);
		}
		y++;
	}
	return (map_copy);
}

int	ft_validate_map_closed(t_game *game)
{
	char	**map_copy;
	int		result;
	int		player_y;
	int		player_x;

	if (ft_find_player_position(game, &player_y, &player_x))
	{
		ft_putstr_fd("Error\nNo player position found", 2);
		ft_putstr_fd(" for flood-fill validation\n", 2);
		return (1);
	}
	map_copy = ft_copy_map(game);
	if (!map_copy)
	{
		ft_putstr_fd("Error\nMemory alloc failed for validation\n", 2);
		return (1);
	}
	result = ft_flood_fill(map_copy, player_y, player_x);
	ft_free_map_copy(map_copy);
	return (result);
}
