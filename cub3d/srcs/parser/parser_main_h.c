/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main_h.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:52:34 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_parser_paths(t_game *game)
{
	if (game->path_north)
	{
		free(game->path_north);
		game->path_north = NULL;
	}
	if (game->path_south)
	{
		free(game->path_south);
		game->path_south = NULL;
	}
	if (game->path_east)
	{
		free(game->path_east);
		game->path_east = NULL;
	}
	if (game->path_west)
	{
		free(game->path_west);
		game->path_west = NULL;
	}
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
}

void	ft_flush_gnl_buffer(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
}
