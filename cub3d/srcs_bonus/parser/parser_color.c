/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:21:31 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	print_color_format_error(void)
{
	ft_putstr_fd("Error\nInvalid color format. Expected: ", 2);
	ft_putstr_fd("F R,G,B or C R,G,B (example: F 255,255,255)\n", 2);
}

static int	ft_strip_newlines_in_values(char **values, int count)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < count)
	{
		tmp = values[i];
		while (tmp && *tmp && *tmp != '\n')
			tmp++;
		if (tmp && *tmp == '\n')
			*tmp = '\0';
		i++;
	}
	return (1);
}

static int	ft_parse_rgb_values(char *line, int *r, int *g, int *b)
{
	char	**values;

	ft_replace_commas_with_spaces(&line[2]);
	values = ft_split(&line[2], ' ');
	if (!values)
		return (1);
	if (ft_count_split(values) != 3)
		return (ft_free_split_arr(values), print_color_format_error(), 1);
	ft_strip_newlines_in_values(values, 3);
	if (ft_check_numeric_values(values))
		return (ft_free_split_arr(values), 1);
	if (ft_validate_range_and_assign(r, g, b, values))
		return (ft_free_split_arr(values), 1);
	ft_free_split_arr(values);
	return (0);
}

/**
* @brief Parses a color line (floor or ceiling).
* 
* Identifies whether it is floor color (F) or ceiling color (C),
* 	extracts the RGB values,
* combines them into a single 32-bit integer,
* 	and stores them in the game structure.
* Also checks for duplicate colors.
* 
* @param line Color configuration line.
* @param game Pointer to the game structure.
* @return int 1 on success, -1 on error.
*/
int	ft_parse_color(char *line, t_game *game)
{
	int	r;
	int	g;
	int	b;
	int	color;

	if (ft_parse_rgb_values(line, &r, &g, &b))
		return (ft_putstr_fd("Error\nInvalid RGB color format\n", 2), -1);
	color = (r << 16) | (g << 8) | b;
	if (!ft_strncmp(line, "F ", 2))
	{
		if (game->floor_color != 0)
			return (ft_putstr_fd("Error\nDuplicate floor color\n", 2), -1);
		game->floor_color = color;
	}
	else if (!ft_strncmp(line, "C ", 2))
	{
		if (game->ceiling_color != 0)
			return (ft_putstr_fd("Error\nDuplicate ceiling color\n", 2), -1);
		game->ceiling_color = color;
	}
	return (1);
}
