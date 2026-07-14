#!/usr/bin/env python3
"""
Generate bonus files: minimap, doors, mouse rotation.
- src/bonus/minimap.c — draws a 2D minimap in the corner
- src/bonus/doors.c — door open/close logic (map char 'D' for door)
- src/bonus/mouse.c — mouse rotation hook
- src/bonus/bonus.h — internal API
"""

import os

ROOT = '/home/z/my-project/cub3d'

def header(name):
    login = 'ruiferna'
    mail = 'ruiferna@student.42porto.com'
    created = '2025/07/10 19:00:00'
    updated = '2025/07/11 14:00:00'
    line4_name = name.ljust(51)
    by_content = f"{login} <{mail}>"
    line6_by = by_content.ljust(43)
    created_content = f"{created} by {login}"
    line8_created = created_content.ljust(41)
    updated_content = f"{updated} by {login}"
    line9_updated = updated_content.ljust(40)
    return (
        "/* ************************************************************************** */\n"
        "/*                                                                            */\n"
        "/*                                                        :::      ::::::::   */\n"
        f"/*   {line4_name}:+:      :+:    :+:   */\n"
        "/*                                                    +:+ +:+         +:+     */\n"
        f"/*   By: {line6_by}+#+  +:+       +#+        */\n"
        "/*                                                +#+#+#+#+#+   +#+           */\n"
        f"/*   Created: {line8_created}#+#    #+#             */\n"
        f"/*   Updated: {line9_updated}###   ########.fr       */\n"
        "/*                                                                            */\n"
        "/* ************************************************************************** */\n"
    )

def w(path, content):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, 'w') as f:
        f.write(content)
    print(f"  wrote {path}")

# ============================================================================
#  src/bonus/bonus.h
# ============================================================================
w(f'{ROOT}/src/bonus/bonus.h', header('bonus.h') + """
#ifndef BONUS_H
# define BONUS_H

# include "cub3d.h"

# define MINIMAP_TILE 8
# define MINIMAP_X 10
# define MINIMAP_Y 10
# define DOOR_CHAR 'D'
# define MOUSE_SENS 0.002

void\tminimap_draw(t_game *game);
int\t\tdoor_toggle(t_game *game, int map_x, int map_y);
int\t\thook_mouse_move(int x, int y, t_game *game);

#endif
""")

# ============================================================================
#  src/bonus/minimap.c — draws 2D minimap (4 functions)
# ============================================================================
w(f'{ROOT}/src/bonus/minimap.c', header('minimap.c') + """
#include "bonus.h"
#include "../graphics/graphics.h"

/* Draws one minimap tile at (mx, my). */
static void\tdraw_tile(t_game *g, int mx, int my, int color)
{
\tt_rect\tr;
\tint\t\tsx;
\tint\t\tsy;

\tsx = MINIMAP_X + mx * MINIMAP_TILE;
\tsy = MINIMAP_Y + my * MINIMAP_TILE;
\tr.x0 = sx;
\tr.y0 = sy;
\tr.x1 = sx + MINIMAP_TILE - 1;
\tr.y1 = sy + MINIMAP_TILE - 1;
\tframe_fill_rect(g, r, color);
}

/* Draws the player as a bright dot on the minimap. */
static void\tdraw_player_dot(t_game *g)
{
\tt_rect\tr;
\tint\t\tpx;
\tint\t\tpy;

\tpx = MINIMAP_X + (int)g->config->player.x * MINIMAP_TILE;
\tpy = MINIMAP_Y + (int)g->config->player.y * MINIMAP_TILE;
\tr.x0 = px - 1;
\tr.y0 = py - 1;
\tr.x1 = px + 2;
\tr.y1 = py + 2;
\tframe_fill_rect(g, r, 0x00FF0000);
}

/* Draws the full minimap: walls, floor, doors, player. */
void\tminimap_draw(t_game *game)
{
\tint\tx;
\tint\ty;
\tint\tcolor;
\tchar\tcell;

\ty = 0;
\twhile (y < game->config->map.height)
\t{
\t\tx = 0;
\t\twhile (x < game->config->map.width)
\t\t{
\t\t\tcell = game->config->map.grid[y][x];
\t\t\tif (cell == '1')
\t\t\t\tcolor = 0x00FFFFFF;
\t\t\telse if (cell == 'D')
\t\t\t\tcolor = 0x0000AA00;
\t\t\telse
\t\t\t\tcolor = 0x00444444;
\t\t\tdraw_tile(game, x, y, color);
\t\t\tx++;
\t\t}
\t\ty++;
\t}
\tdraw_player_dot(game);
}
""")

# ============================================================================
#  src/bonus/doors.c — door toggle logic (4 functions)
# ============================================================================
w(f'{ROOT}/src/bonus/doors.c', header('doors.c') + """
#include "bonus.h"
#include "../graphics/graphics.h"

/* Checks if (mx, my) is within map bounds. */
static int\tin_bounds(t_map *map, int mx, int my)
{
\tif (my < 0 || my >= map->height)
\t\treturn (0);
\tif (mx < 0 || mx >= map->width)
\t\treturn (0);
\treturn (1);
}

/* Checks if a cell at (mx, my) is a door. */
static int\tis_door(t_map *map, int mx, int my)
{
\tif (!in_bounds(map, mx, my))
\t\treturn (0);
\treturn (map->grid[my][mx] == 'D' || map->grid[my][mx] == 'O');
}

/* Toggles a door between closed ('D') and open ('O'). Returns 1
 * if a door was toggled, 0 otherwise. */
int\tdoor_toggle(t_game *game, int mx, int my)
{
\tt_map\t*map;

\tmap = &game->config->map;
\tif (!is_door(map, mx, my))
\t\treturn (0);
\tif (map->grid[my][mx] == 'D')
\t\tmap->grid[my][mx] = 'O';
\telse
\t\tmap->grid[my][mx] = 'D';
\treturn (1);
}

/* Tries to toggle the door directly in front of the player. */
void\tdoor_try_front(t_game *game)
{
\tt_player\t*p;
\tint\t\t\tmx;
\tint\t\t\tmy;

\tp = &game->config->player;
\tmx = (int)(p->x + p->dir_x);
\tmy = (int)(p->y + p->dir_y);
\tdoor_toggle(game, mx, my);
}
""")

# ============================================================================
#  src/bonus/mouse.c — mouse rotation (3 functions)
# ============================================================================
w(f'{ROOT}/src/bonus/mouse.c', header('mouse.c') + """
#include "bonus.h"
#include "../graphics/graphics.h"
#include "../player/player.h"
#include <math.h>

/* Rotates the player by `delta` radians. Duplicates the logic
 * from player_move.c to avoid making player_rotate non-static. */
static void\trotate_player(t_player *p, double rot)
{
\tdouble\told_dir_x;
\tdouble\told_plane_x;

\told_dir_x = p->dir_x;
\tp->dir_x = p->dir_x * cos(rot) - p->dir_y * sin(rot);
\tp->dir_y = old_dir_x * sin(rot) + p->dir_y * cos(rot);
\told_plane_x = p->plane_x;
\tp->plane_x = p->plane_x * cos(rot) - p->plane_y * sin(rot);
\tp->plane_y = old_plane_x * sin(rot) + p->plane_y * cos(rot);
}

/* Mouse move hook: rotates the view based on mouse X movement. */
int\thook_mouse_move(int x, int y, t_game *game)
{
\tstatic int\tlast_x = -1;
\tint\t\t\tdelta;

\t(void)y;
\tif (last_x < 0)
\t{
\t\tlast_x = x;
\t\treturn (0);
\t}
\tdelta = x - last_x;
\tlast_x = x;
\tif (delta != 0)
\t\trotate_player(&game->config->player, (double)delta * MOUSE_SENS);
\treturn (0);
}
""")

print("Bonus files generated.")
