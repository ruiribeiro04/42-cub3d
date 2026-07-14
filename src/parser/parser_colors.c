/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/11 16:00:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser_internal.h"
#include <libft.h>

static int	parse_color_component(const char **p, int *out)
{
	int	value;

	skip_spaces(p);
	if (!ft_isdigit(**p))
		return (cub_error_int("Color component must be a number"));
	value = 0;
	while (ft_isdigit(**p))
	{
		value = value * 10 + (**p - '0');
		if (value > 255)
			return (cub_error_int("Color out of range [0,255]"));
		(*p)++;
	}
	*out = value;
	return (0);
}

static int	expect_comma(const char **p)
{
	skip_spaces(p);
	if (**p != ',')
		return (cub_error_int("Expected ',' between components"));
	(*p)++;
	return (0);
}

static int	store_color(char target, t_config *cfg, t_color *color)
{
	if (target == 'F' && !cfg->has_floor)
	{
		cfg->floor = *color;
		cfg->has_floor = 1;
		return (0);
	}
	if (target == 'C' && !cfg->has_ceiling)
	{
		cfg->ceiling = *color;
		cfg->has_ceiling = 1;
		return (0);
	}
	return (cub_error_int("Duplicate color identifier"));
}

int	parse_color_line(const char *line, t_config *cfg)
{
	const char	*p;
	t_color		color;

	if (line[1] != ' ' && line[1] != '\t')
		return (cub_error_int("Color id must be followed by ws"));
	p = line + 1;
	if (parse_color_component(&p, &color.r) < 0)
		return (-1);
	if (expect_comma(&p) < 0
		|| parse_color_component(&p, &color.g) < 0)
		return (-1);
	if (expect_comma(&p) < 0
		|| parse_color_component(&p, &color.b) < 0)
		return (-1);
	skip_spaces(&p);
	if (*p != '\0')
		return (cub_error_int("Unexpected text after color"));
	return (store_color(line[0], cfg, &color));
}
