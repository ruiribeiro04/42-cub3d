/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/11 16:00:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser_internal.h"
#include <libft.h>

static int	is_space_char(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_blank_line(const char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i] != '\0')
	{
		if (!is_space_char(line[i]))
			return (0);
		i++;
	}
	return (1);
}

void	skip_spaces(const char **p)
{
	if (!p || !*p)
		return ;
	while (is_space_char(**p))
		(*p)++;
}

int	is_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ' || c == 'D'
		|| c == 'O' || c == '2');
}

int	looks_like_map(const char *line)
{
	int	i;
	int	has_one;

	if (!line)
		return (0);
	i = 0;
	has_one = 0;
	while (line[i] != '\0')
	{
		if (!is_map_char(line[i]))
			return (0);
		if (line[i] == '1')
			has_one = 1;
		i++;
	}
	return (has_one);
}
