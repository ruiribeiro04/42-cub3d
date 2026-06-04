/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:51:42 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_parse_element_line(char *line, t_game *game)
{
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		return (ft_parse_texture(line, game));
	else if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		return (ft_parse_color(line, game));
	return (-1);
}

static int	ft_handle_element_line(char *line, t_game *game)
{
	int	ret;

	if (!ft_is_element_line(line))
		return (0);
	ret = ft_parse_element_line(line, game);
	if (ret == 1)
	{
		ft_putstr_fd("Error\nInvalid or duplicate config elements\n", 2);
		return (1);
	}
	return (0);
}

static int	ft_process_element_loop(int fd, t_game *game, char **out_line)
{
	char	*line;

	line = ft_skip_empty_lines(fd);
	while (line && !ft_is_map_line(line))
	{
		if (ft_handle_element_line(line, game) == 1)
		{
			free(line);
			return (1);
		}
		free(line);
		line = ft_skip_empty_lines(fd);
	}
	*out_line = line;
	return (0);
}

char	*ft_parse_elements(int fd, t_game *game)
{
	char	*line;

	if (ft_process_element_loop(fd, game, &line) == 1)
		return (NULL);
	if (!ft_has_all_required_elements(game))
	{
		if (line)
			free(line);
		ft_print_missing_elements_error();
		return (NULL);
	}
	return (line);
}
