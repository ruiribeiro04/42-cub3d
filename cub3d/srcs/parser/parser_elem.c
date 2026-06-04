/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_elem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:52:21 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_elem.c
 * @brief Parse a single element line (texture or color) from the .cub file.
 */

#include "cub3d.h"

/**
 * @ingroup parser
 */
int	ft_is_element_line(char *line)
{
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3))
		return (1);
	if (!ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		return (1);
	if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		/**
		 * @ingroup parser
		 */
		return (1);
	return (0);
}

int	ft_is_map_line(char *line)
{
	if (!line || line[0] == '\n' || line[0] == '\0')
		return (0);
	while (line[0] == ' ' || line[0] == '\t')
		line++;
	if (line[0] == '0' || line[0] == '1' || line[0] == '2')
		return (1);
	if (line[0] == 'N' || line[0] == 'S' || line[0] == 'E' || line[0] == 'W')
	{
		/**
		 * @ingroup parser
		 */
		if (line[1] == ' ' || line[1] == '\t' || line[1] == '\n'
			|| line[1] == '\0')
			return (1);
	}
	return (0);
}

int	ft_has_all_required_elements(t_game *game)
{
	if (!game->path_north || !game->path_south)
		return (0);
	if (!game->path_east || !game->path_west)
		return (0);
	if (!game->floor_color_set || !game->ceiling_color_set)
		return (0);
	return (1);
}

char	*ft_skip_empty_lines(int fd)
{
	char	*line;

	line = get_next_line(fd);
	/**
	 * @ingroup parser
	 */
	while (line && line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

void	ft_print_missing_elements_error(void)
{
	ft_putstr_fd("Error\nMissing required config elements", 2);
	ft_putstr_fd(" (NO, SO, WE, EA, F, C)\n", 2);
}
