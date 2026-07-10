/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:52:06 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_texture.c
 * @brief Validate the four wall texture files exist and are readable.
 */

#include "cub3d.h"

static char	*extract_path(char *line, int start)
{
	int		i;
	int		len;
	char	*path;

	i = start;
	while (line[i] && line[i] == ' ')
		i++;
	path = ft_strdup(&line[i]);
	if (!path)
		return (NULL);
	i = 0;
	while (path[i] && path[i] != '\n')
		i++;
	path[i] = '\0';
	len = ft_strlen(path);
	while (len > 0 && (path[len - 1] == ' ' || path[len - 1] == '\t'))
	{
		path[len - 1] = '\0';
		len--;
	}
	if (len == 0)
		return (free(path), NULL);
	return (path);
}

static int	parse_one_cardinal(char *line, t_game *game)
{
	char	*path;
	char	**slot;

	path = extract_path(line, 3);
	if (!path)
		return (1);
	slot = ft_select_texture_slot(line, game);
	if (!slot)
	{
		ft_putstr_fd("Error\nUnknown texture direction\n", 2);
		free(path);
		return (1);
	}
	if (*slot)
	{
		ft_putstr_fd("Error\nDuplicate texture\n", 2);
		free(path);
		return (1);
	}
	*slot = path;
	return (0);
}

int	validate_texture_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nCannot open texture file: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	close(fd);
	return (0);
}

int	validate_all_textures(t_game *game)
{
	int	errors;

	errors = 0;
	if (!game->path_north || validate_texture_path(game->path_north))
		errors++;
	if (!game->path_south || validate_texture_path(game->path_south))
		errors++;
	if (!game->path_east || validate_texture_path(game->path_east))
		errors++;
	if (!game->path_west || validate_texture_path(game->path_west))
		errors++;
	return (errors);
}

/**
 * @ingroup parser
 */
int	ft_parse_texture(char *line, t_game *game)
{
	if (parse_one_cardinal(line, game) == 1)
		return (1);
	return (0);
}
