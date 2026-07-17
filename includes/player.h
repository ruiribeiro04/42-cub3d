/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 19:56:03 by ruiferna          #+#    #+#             */
/*   Updated: 2026/07/17 17:09:00 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "cub3d.h"

void	ft_player_init_direction(t_player *p);
void	ft_player_update(t_game *game);
void	ft_apply_movement(t_game *game, t_player *p, t_keys *k);
void	ft_player_rotate(t_player *p, double rot);

#endif
