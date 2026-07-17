/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/14 16:00:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"
#include <fcntl.h>
#include <unistd.h>

int	ft_path_readable(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	ft_map_in_bounds(const t_map *map, int x, int y)
{
	if (y < 0 || y >= map->height)
		return (0);
	if (x < 0 || x >= map->width)
		return (0);
	return (1);
}

/*
 * Single source of truth for "does this cell block movement / rays / the
 * flood fill". Walls ('1') and closed doors ('D') are barriers; everything
 * else ('0', 'O', ...) is walkable.  The grid never contains ' ' — ft_pad_line
 * converts every void cell to '1' so the whole map is a solid block of
 * walls with walkable cells carved out, exactly like the reference parser.
 */
int	is_barrier(char c)
{
	return (c == '1' || c == 'D');
}
