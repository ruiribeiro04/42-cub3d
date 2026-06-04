/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_val_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:52:46 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_print_invalid_char_error(char c, int y, int x)
{
	ft_putstr_fd("Error\nInvalid character '", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("' at map position (", 2);
	ft_putnbr_fd(y, 2);
	ft_putstr_fd(", ", 2);
	ft_putnbr_fd(x, 2);
	ft_putstr_fd(")\n", 2);
}

int	ft_is_valid_map_char(char c)
{
	if (c == '0' || c == '1' || c == '2' || c == 'D' || c == ' ' || c == '\t')
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	ft_check_row_chars(char **map, int y)
{
	int	x;

	x = 0;
	while (map[y][x])
	{
		if (!ft_is_valid_map_char(map[y][x]))
		{
			ft_print_invalid_char_error(map[y][x], y, x);
			return (1);
		}
		x++;
	}
	return (0);
}

int	ft_find_player_position(t_game *game, int *py, int *px)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'N' || game->map[y][x] == 'S'
				|| game->map[y][x] == 'E' || game->map[y][x] == 'W')
			{
				*py = y;
				*px = x;
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}
