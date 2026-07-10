/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_val_flood.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:52:41 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_val_flood.c
 * @brief Flood-fill algorithm for map closure validation.
 */

#include "cub3d.h"

#define FLOOD_STACK_MAX 4096

static void	ft_print_breach(int y, int x)
{
	ft_putstr_fd("Error\nMap not closed - boundary breach at (", 2);
	ft_putnbr_fd(y, 2);
	ft_putstr_fd(", ", 2);
	ft_putnbr_fd(x, 2);
	ft_putstr_fd(")\n", 2);
}

static int	ft_flood_step(char **map_copy, int y, int x)
{
	int	line_length;

	if (y < 0 || !map_copy[y])
		return (ft_print_breach(y, x), 1);
	line_length = ft_strlen(map_copy[y]);
	if (x < 0 || x >= line_length)
		return (ft_print_breach(y, x), 1);
	return (0);
}

static int	ft_is_wall(char c)
{
	return (c == '1' || c == '2' || c == 'D' || c == ' ' || c == 'V');
}

static int	ft_push_neighbor(t_point *stack, int top, int ny, int nx)
{
	t_point	p;

	if (top >= FLOOD_STACK_MAX - 1)
		return (ft_putstr_fd("Error\nMap too complex\n", 2), -1);
	p.x = nx;
	p.y = ny;
	stack[top] = p;
	return (top + 1);
}

/**
 * @ingroup parser
 */
int	ft_flood_fill(char **map_copy, int y, int x)
{
	t_point	stack[FLOOD_STACK_MAX];
	int		top;
	t_point	cur;

	top = 0;
	top = ft_push_neighbor(stack, top, y, x);
	if (top == -1)
		return (1);
	while (top > 0)
	{
		cur = stack[--top];
		if (ft_flood_step(map_copy, cur.y, cur.x) == 1)
			return (1);
		if (ft_is_wall(map_copy[cur.y][cur.x]))
			continue ;
		map_copy[cur.y][cur.x] = 'V';
		top = ft_push_neighbor(stack, top, cur.y - 1, cur.x);
		if (top == -1)
			return (1);
		top = ft_push_neighbor(stack, top, cur.y + 1, cur.x);
		if (top == -1)
			return (1);
		top = ft_push_neighbor(stack, top, cur.y, cur.x - 1);
		if (top == -1)
			return (1);
		top = ft_push_neighbor(stack, top, cur.y, cur.x + 1);
		if (top == -1)
			return (1);
	}
	return (0);
}
