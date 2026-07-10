/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:21:41 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_main.c
 * @brief Main parser orchestration for the bonus tree.
 */

#include "cub3d.h"

static int	ft_parse_and_validate(t_game *game, int fd, char *first_line);

int	ft_parse_cub_file(char *filename, t_game *game)
{
	int		fd;
	char	*first_line;

	fd = ft_open_and_validate(filename);
	if (fd < 0)
		return (1);
	first_line = ft_parse_elements(fd, game);
	if (!first_line)
	{
		close(fd);
		return (1);
	}
	if (ft_parse_and_validate(game, fd, first_line))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	ft_open_and_validate(char *filename)
{
	int	len;
	int	fd;

	len = 0;
	while (filename[len])
		len++;
	if (len < 4 || ft_strncmp(&filename[len - 4], ".cub", 4))
	{
		ft_putstr_fd("Error\nInvalid file extension. Must be .cub\n", 2);
		return (-1);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nCannot open file ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd("\n", 2);
	}
	return (fd);
}

static int	ft_parse_and_validate(t_game *game, int fd, char *first_line)
{
	game->map = ft_parse_map_grid(fd, game, first_line);
	if (!game->map)
		return (1);
	if (ft_validate_map_chars(game) || ft_validate_map_closed(game))
	{
		ft_free_parser_paths(game);
		ft_free_parser_map(game);
		return (1);
	}
	if (ft_parse_doors(game) == 1)
	{
		ft_free_parser_paths(game);
		ft_free_parser_map(game);
		return (1);
	}
	if (ft_extract_sprites(game) == 1 || ft_init_player_from_map(game) == 1)
	{
		ft_free_doors(game);
		ft_free_parsed_sprites(game);
		ft_free_parser_paths(game);
		ft_free_parser_map(game);
		return (1);
	}
	return (0);
}
