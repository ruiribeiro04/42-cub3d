/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/11 16:00:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser_internal.h"
#include <stdlib.h>
#include <libft.h>

int	ft_validate_map_line(const char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!ft_is_map_char(line[i]))
			return (ft_cub_error_int("Invalid character in map"));
		i++;
	}
	return (0);
}

char	*ft_pad_line(const char *src, int width)
{
	char	*dst;
	int		src_len;
	int		i;

	dst = (char *)malloc(sizeof(char) * (width + 1));
	if (!dst)
		return (NULL);
	src_len = (int)ft_strlen(src);
	i = 0;
	while (i < src_len && i < width)
	{
		if (src[i] == ' ')
			dst[i] = '1';
		else
			dst[i] = src[i];
		i++;
	}
	while (i < width)
	{
		dst[i] = '1';
		i++;
	}
	dst[width] = '\0';
	return (dst);
}

static void	free_grid_partial(char **grid, int count,
								t_map_collector *c)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
	ft_collector_free(c);
}

static int	build_grid(t_config *cfg, t_map_collector *c)
{
	char	**grid;
	int		i;

	grid = (char **)malloc(sizeof(char *) * (c->count + 1));
	if (!grid)
		return (ft_cub_error_int("Memory allocation failed"));
	i = 0;
	while (i < c->count)
	{
		grid[i] = ft_pad_line(c->lines[i], c->max_width);
		if (!grid[i])
		{
			ft_cub_error("Memory allocation failed");
			free_grid_partial(grid, i, c);
			return (-1);
		}
		i++;
	}
	grid[c->count] = NULL;
	cfg->map.grid = grid;
	cfg->map.height = c->count;
	cfg->map.width = c->max_width;
	return (0);
}

int	ft_finalize_map(t_config *cfg, t_map_collector *c)
{
	if (c->count == 0)
	{
		ft_cub_error("No map found");
		ft_collector_free(c);
		return (-1);
	}
	if (build_grid(cfg, c) < 0)
		return (-1);
	ft_collector_free(c);
	if (ft_find_spawn(cfg) < 0)
		return (-1);
	return (ft_flood_fill_check(cfg));
}
