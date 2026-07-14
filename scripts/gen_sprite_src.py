#!/usr/bin/env python3
"""Generate sprite rendering and animation source files."""

import os

ROOT = '/home/z/my-project/cub3d'

def header(name):
    login = 'ruiferna'
    mail = 'ruiferna@student.42porto.com'
    created = '2025/07/10 19:00:00'
    updated = '2025/07/11 15:00:00'
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
#  src/bonus/sprites.h
# ============================================================================
w(f'{ROOT}/src/bonus/sprites.h', header('sprites.h') + """
#ifndef SPRITES_H
# define SPRITES_H

# include "cub3d.h"

void\tsprites_render(t_game *game);
void\tsprites_update(t_game *game);
int\t\tsprites_init(t_game *game);
void\tsprites_cleanup(t_game *game);

#endif
""")

# ============================================================================
#  src/bonus/sprites_init.c — count '2' positions, allocate, fill (4 funcs)
# ============================================================================
w(f'{ROOT}/src/bonus/sprites_init.c', header('sprites_init.c') + """
#include "sprites.h"
#include "../graphics/graphics.h"
#include "../parser/parser_internal.h"
#include <stdlib.h>

/* Counts how many '2' chars are in the original map.
 * Since find_spawn already converted them to '0', we can't scan the grid.
 * Instead, we use a stored count from the parser. For simplicity, we
 * re-scan the config's sprite_texture presence + a stored count. */
static int\tcount_map_sprites(t_config *cfg)
{
\t(void)cfg;
\treturn (0);
}

/* Actually, the '2' chars were converted to '0' by convert_sprites_to_floor.
 * We need to count them BEFORE conversion. Let's change approach:
 * store the count in t_config during parsing. For now, return 0. */
int\tsprites_init(t_game *game)
{
\tt_config\t*cfg;
\tint\t\t\tcount;

\tcfg = game->config;
\tcount = count_map_sprites(cfg);
\tif (count == 0)
\t{
\t\tgame->has_sprites = 0;
\t\treturn (0);
\t}
\tgame->sprites = (t_sprite *)malloc(sizeof(t_sprite) * count);
\tif (!game->sprites)
\t\treturn (cub_error_int("Failed to alloc sprites"));
\tgame->num_sprites = count;
\tgame->has_sprites = 1;
\treturn (0);
}

/* Cleanup is handled by game_cleanup (free(game->sprites)). */
void\tsprites_cleanup(t_game *game)
{
\t(void)game;
}
""")

# Hmm, the problem is that convert_sprites_to_floor already replaced '2'
# with '0', so we can't find sprite positions in game_init. I need to
# store sprite positions during parsing, before conversion.
#
# Better approach: add a sprite_positions array to t_config, filled during
# parsing (before conversion), then game_init copies them to t_game.
#
# Let me restructure: add to t_config:
#   t_sprite *sprite_positions;
#   int num_sprite_positions;
# Fill these in find_spawn (scan for '2', record positions, THEN convert).
# game_init allocates game->sprites and copies from config.

print("sprites_init.c generated (will be rewritten below)")

# ============================================================================
#  Rewrite sprites_init.c properly — uses config->sprite_positions
# ============================================================================
w(f'{ROOT}/src/bonus/sprites_init.c', header('sprites_init.c') + """
#include "sprites.h"
#include "../graphics/graphics.h"
#include <stdlib.h>

/* Allocates the sprite array and copies positions from config.
 * The positions were collected during parsing (before '2'->'0'). */
int\tsprites_init(t_game *game)
{
\tt_config\t*cfg;
\tint\t\t\ti;

\tcfg = game->config;
\tif (!cfg->has_sprite || cfg->num_sprites == 0)
\t{
\t\tgame->has_sprites = 0;
\t\treturn (0);
\t}
\tgame->sprites = (t_sprite *)malloc(sizeof(t_sprite) * cfg->num_sprites);
\tif (!game->sprites)
\t\treturn (cub_error_int("Failed to alloc sprites"));
\ti = 0;
\twhile (i < cfg->num_sprites)
\t{
\t\tgame->sprites[i].x = cfg->sprite_positions[i].x;
\t\tgame->sprites[i].y = cfg->sprite_positions[i].y;
\t\tgame->sprites[i].distance = 0.0;
\t\ti++;
\t}
\tgame->num_sprites = cfg->num_sprites;
\tgame->has_sprites = 1;
\treturn (0);
}

/* Cleanup is handled by game_cleanup (free(game->sprites)). */
void\tsprites_cleanup(t_game *game)
{
\t(void)game;
}
""")

print("sprites_init.c rewritten properly")
