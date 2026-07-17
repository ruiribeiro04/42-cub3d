/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_common.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:45:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/15 14:45:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser_internal.h"
#include <libft.h>

/*
 * Common helper functions shared between the mandatory and bonus parser
 * builds. The only function that differs between the two builds is
 * ft_is_map_char() — see parser_utils.c and parser_utils_bonus.c.
 */

static int	ft_is_space_char(char c)
{
	return (c == ' ' || c == '\t');
}

int	ft_is_blank_line(const char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i] != '\0')
	{
		if (!ft_is_space_char(line[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_skip_spaces(const char **p)
{
	if (!p || !*p)
		return ;
	while (ft_is_space_char(**p))
		(*p)++;
}

int	ft_looks_like_map(const char *line)
{
	int	i;
	int	has_one;

	if (!line)
		return (0);
	i = 0;
	has_one = 0;
	while (line[i] != '\0')
	{
		if (!ft_is_map_char(line[i]))
			return (0);
		if (line[i] == '1')
			has_one = 1;
		i++;
	}
	return (has_one);
}
