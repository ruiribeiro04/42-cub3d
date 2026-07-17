/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 19:40:20 by ruiferna          #+#    #+#             */
/*   Updated: 2026/07/17 17:07:34 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# include "cub3d.h"

# define MINIMAP_TILE 8
# define MINIMAP_X 10
# define MINIMAP_Y 10
# define MINIMAP_MAX_TILES_X	150
# define MINIMAP_MAX_TILES_Y	80
# define MINIMAP_BORDER_THICKNESS 2
# define MINIMAP_BG_COLOR      0x00000000
# define MINIMAP_BORDER_COLOR  0x00FFFFFF
# define MINIMAP_WALL_COLOR    0x00FFFFFF
# define MINIMAP_FLOOR_COLOR   0x00808080
# define MINIMAP_VOID_COLOR    0x00000000
# define MINIMAP_DOOR_COLOR    0x00CC8800
# define MINIMAP_OPEN_COLOR    0x0000CC00
# define MINIMAP_PLAYER_COLOR  0x00FF2222
# define MINIMAP_DIR_COLOR     0x00FFFF00

void	ft_minimap_draw(t_game *game);
void	ft_door_try_front(t_game *game);
int		ft_hook_mouse_move(int x, int y, t_game *game);
int		ft_hook_focus_in(t_game *game);
int		ft_hook_focus_out(t_game *game);

#endif
