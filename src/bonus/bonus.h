/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/11 16:00:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef BONUS_H
# define BONUS_H

# include "cub3d.h"

# define MINIMAP_TILE 8
# define MINIMAP_X 10
# define MINIMAP_Y 10

void	minimap_draw(t_game *game);
void	door_try_front(t_game *game);
int		hook_mouse_move(int x, int y, t_game *game);
int		hook_focus_in(t_game *game);
int		hook_focus_out(t_game *game);

#endif
