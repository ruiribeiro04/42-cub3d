/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/11 16:00:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "player.h"
#include "../graphics/graphics.h"

static void	set_vertical(t_player *p, int is_north)
{
	p->dir_x = 0;
	p->plane_y = 0;
	p->plane_x = 0.66;
	if (is_north)
		p->dir_y = -1;
	else
	{
		p->dir_y = 1;
		p->plane_x = -0.66;
	}
}

static void	set_horizontal(t_player *p, int is_east)
{
	p->dir_y = 0;
	p->plane_x = 0;
	p->plane_y = 0.66;
	if (is_east)
		p->dir_x = 1;
	else
	{
		p->dir_x = -1;
		p->plane_y = -0.66;
	}
}

void	player_init_direction(t_player *p)
{
	if (p->direction == 'N')
		set_vertical(p, 1);
	else if (p->direction == 'S')
		set_vertical(p, 0);
	else if (p->direction == 'E')
		set_horizontal(p, 1);
	else if (p->direction == 'W')
		set_horizontal(p, 0);
}
