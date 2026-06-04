/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:21:27 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_color_utils.c
 * @brief Color parsing utility helpers.
 */

#include "cub3d.h"

/**
 * @ingroup parser
 */
void	ft_free_split_arr(char **values)
{
	int	i;

	i = 0;
	while (values[i])
	{
		free(values[i]);
		/**
		 * @ingroup parser
		 */
		i++;
	}
	free(values);
}

int	ft_is_valid_number(char *str)
{
	if (!str || !*str)
		return (0);
	while (*str)
	{
		/**
		 * @ingroup parser
		 */
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

/**
 * @ingroup parser
 */
void	ft_replace_commas_with_spaces(char *str)
{
	while (*str)
	{
		if (*str == ',')
			*str = ' ';
		str++;
	}
}

int	ft_validate_range_and_assign(int *r, int *g, int *b, char **values)
{
	*r = ft_atoi(values[0]);
	*g = ft_atoi(values[1]);
	*b = ft_atoi(values[2]);
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
	{
		ft_putstr_fd("Error\nColor values out of range (0-255): ", 2);
		ft_putnbr_fd(*r, 2);
		ft_putstr_fd(",", 2);
		ft_putnbr_fd(*g, 2);
		ft_putstr_fd(",", 2);
		ft_putnbr_fd(*b, 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	return (0);
}
