/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:17:34 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 64

# define COLLISION_MARGIN 0.15f

# define MOUSE_SPEED 0.002f

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define ESC 65307
# define Q 113
# define E 101

# define PI 3.14159265359
# define TWO_PI 6.283185307f
# define FOV 1.0471975512f
# define PLANE_LEN 0.57735026919f
# define MOVE_SPEED 0.05f
# define ROTATE_SPEED 0.03f

# define KEY_PRESS 2
# define KEY_PRESS_MASK 1
# define KEY_RELEASE 3
# define KEY_RELEASE_MASK 2
# define DESTROY_NOTIFY 17
# define STRUCTURE_NOTIFY_MASK 131072

# define MOTION_NOTIFY 6
# define POINTER_MOTION_MASK 64

# define MAP_TILE 10
# define MAP_OFFSET_X 10
# define MAP_OFFSET_Y 10
# define MAP_COLOR_WALL 0xFFF1E8
# define MAP_COLOR_BG 0x1C1B1B
# define MAP_COLOR_PLAYER 0xFF4242
# define MAP_COLOR_DOOR 0xFFCF29

# define DOOR_SPEED 2.0f
# define DOOR_INTERACT_DIST 0.6f

#endif
