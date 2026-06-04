/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:19:21 by ruiferna         ###   ########.fr       */
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

static int	ft_count_split(char **values)
{
	int	count;

	count = 0;
	while (values[count])
		count++;
	return (count);
}

static int	ft_parse_rgb_values(char *line, int *r, int *g, int *b)
{
	char	*str;
	char	**values;
	int		result;

	str = &line[2];
	ft_replace_commas_with_spaces(str);
	values = ft_split(str, ' ');
	if (!values)
		return (1);
	result = 0;
	if (ft_count_split(values) != 3)
	{
		print_color_format_error();
		result = 1;
	}
	if (!result)
		ft_strip_newlines_in_values(values, 3);
	if (!result)
		result = ft_check_numeric_values(values);
	if (!result)
		result = ft_validate_range_and_assign(r, g, b, values);
	ft_free_split_arr(values);
	return (result);
}

int	ft_parse_color(char *line, t_game *game)
{
	int	r;
	int	g;
	int	b;
	int	color;

	if (ft_parse_rgb_values(line, &r, &g, &b))
		return (ft_putstr_fd("Error\nInvalid RGB color format\n", 2), 1);
	color = (r << 16) | (g << 8) | b;
	if (!ft_strncmp(line, "F ", 2))
	{
		if (game->floor_color_set)
			return (ft_putstr_fd("Error\nDuplicate floor color\n", 2), 1);
		game->floor_color = color;
		game->floor_color_set = 1;
	}
	else if (!ft_strncmp(line, "C ", 2))
	{
		if (game->ceiling_color_set)
			return (ft_putstr_fd("Error\nDuplicate ceiling color\n", 2), 1);
		game->ceiling_color = color;
		game->ceiling_color_set = 1;
	}
	return (0);
}
