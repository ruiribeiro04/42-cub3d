/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 12:21:47 by ruiferna          #+#    #+#             */
/*   Updated: 2026/07/17 17:25:54 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"

static int	check_missing(int present, const char *name)
{
	if (!present)
		return (ft_cub_error_int(name));
	return (0);
}

int	ft_validate_config(t_config *cfg)
{
	if (check_missing(cfg->has_north, "Missing NO texture") < 0
		|| check_missing(cfg->has_south, "Missing SO texture") < 0
		|| check_missing(cfg->has_west, "Missing WE texture") < 0
		|| check_missing(cfg->has_east, "Missing EA texture") < 0
		|| check_missing(cfg->has_floor, "Missing F color") < 0
		|| check_missing(cfg->has_ceiling, "Missing C color") < 0
		|| check_missing(cfg->has_player, "Missing player spawn") < 0)
		return (-1);
	return (0);
}
