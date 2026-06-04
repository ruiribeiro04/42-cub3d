/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture_h.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         :+:     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:52:06 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**ft_select_texture_slot(char *line, t_game *game)
{
	if (!ft_strncmp(line, "NO ", 3))
		return (&game->path_north);
	if (!ft_strncmp(line, "SO ", 3))
		return (&game->path_south);
	if (!ft_strncmp(line, "WE ", 3))
		return (&game->path_west);
	if (!ft_strncmp(line, "EA ", 3))
		return (&game->path_east);
	return (NULL);
}
