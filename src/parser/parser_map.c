/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/15 16:00:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser_internal.h"
#include <stdlib.h>
#include <libft.h>

static int	collector_grow(t_map_collector *c)
{
	char	**new_lines;
	int		new_cap;
	int		i;

	new_cap = c->capacity * 2;
	new_lines = (char **)malloc(sizeof(char *) * new_cap);
	if (!new_lines)
		return (cub_error_int("Memory allocation failed"));
	i = 0;
	while (i < c->count)
	{
		new_lines[i] = c->lines[i];
		i++;
	}
	free(c->lines);
	c->lines = new_lines;
	c->capacity = new_cap;
	return (0);
}

int	collector_init(t_map_collector *c, char *first_line)
{
	c->capacity = 16;
	c->lines = (char **)malloc(sizeof(char *) * c->capacity);
	if (!c->lines)
	{
		cub_error("Memory allocation failed");
		free(first_line);
		return (-1);
	}
	c->lines[0] = first_line;
	c->count = 1;
	c->max_width = 0;
	if (first_line)
		c->max_width = (int)ft_strlen(first_line);
	return (0);
}

int	collector_add(t_map_collector *c, char *line)
{
	int	line_len;

	if (c->count >= c->capacity)
	{
		if (collector_grow(c) < 0)
		{
			free(line);
			return (-1);
		}
	}
	c->lines[c->count] = line;
	line_len = (int)ft_strlen(line);
	if (line_len > c->max_width)
		c->max_width = line_len;
	c->count++;
	return (0);
}

void	collector_free(t_map_collector *c)
{
	int	i;

	if (!c->lines)
		return ;
	i = 0;
	while (i < c->count)
	{
		free(c->lines[i]);
		i++;
	}
	free(c->lines);
	c->lines = NULL;
}

int	parse_map_block(int fd, char *first_line, t_config *cfg)
{
	t_map_collector	c;
	char			*line;

	if (process_map_line(&first_line) < 0)
		return (-1);
	if (collector_init(&c, first_line) < 0)
		return (-1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		strip_newline(line);
		if (process_map_line(&line) < 0)
		{
			collector_free(&c);
			return (-1);
		}
		if (collector_add(&c, line) < 0)
		{
			collector_free(&c);
			return (-1);
		}
		line = get_next_line(fd);
	}
	return (finalize_map(cfg, &c));
}
