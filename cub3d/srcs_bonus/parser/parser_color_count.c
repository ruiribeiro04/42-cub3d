/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color_count.c                               :+:      :+:    :+:   */
/*                                                    +:+     :+:    :+:     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:21:27 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_color_count.c
 * @brief Count and validate comma-separated color values.
 */

#include "cub3d.h"

/**
 * @ingroup parser
 */
int	ft_count_split(char **values)
{
	int	i;

	i = 0;
	while (values[i])
		i++;
	return (i);
}
