/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_val_flood.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:52:41 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_val_flood.c
 * @brief Flood-fill algorithm for map closure validation.
 */

#include "cub3d.h"

static void	ft_print_breach(int y, int x)
{
	ft_putstr_fd("Error\nMap not closed - boundary breach at (", 2);
	ft_putnbr_fd(y, 2);
	ft_putstr_fd(", ", 2);
	ft_putnbr_fd(x, 2);
	ft_putstr_fd(")\n", 2);
}

static int	ft_flood_step(char **map_copy, int y, int x)
{
	int	line_length;

	if (y < 0)
		return (ft_print_breach(y, x), 1);
	line_length = ft_strlen(map_copy[y]);
	if (x < 0 || x >= line_length)
		return (ft_print_breach(y, x), 1);
	return (0);
}

/**
 * @ingroup parser
 */
int	ft_flood_fill(char **map_copy, int y, int x)
{
	char	c;

	if (ft_flood_step(map_copy, y, x) == 1)
		return (1);
	c = map_copy[y][x];
	if (c == '1' || c == '2' || c == 'D' || c == ' ' || c == 'V')
		return (0);
	map_copy[y][x] = 'V';
	if (ft_flood_fill(map_copy, y - 1, x))
		return (1);
	if (ft_flood_fill(map_copy, y + 1, x))
		return (1);
	if (ft_flood_fill(map_copy, y, x - 1))
		return (1);
	return (ft_flood_fill(map_copy, y, x + 1));
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
