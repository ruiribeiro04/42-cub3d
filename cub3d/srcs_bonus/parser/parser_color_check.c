/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color_check.c                               :+:      :+:    :+:   */
/*                                                    +:+     :+:    :+:     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:21:27 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_numeric_values(char **values)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!ft_is_valid_number(values[i]))
		{
			ft_putstr_fd("Error\nColor values must be numeric (0-255)\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}
