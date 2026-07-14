#!/usr/bin/env python3
"""Generate sprites.h with t_sprite_draw + sprite_anim.c with sort + anim."""

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
#  src/bonus/sprites.h — with t_sprite_draw + all declarations
# ============================================================================
w(f'{ROOT}/src/bonus/sprites.h', header('sprites.h') + """
#ifndef SPRITES_H
# define SPRITES_H

# include "cub3d.h"

/* Drawing parameters for a single sprite. */
typedef struct s_sprite_draw
{
\tint\tscreen_x;
\tint\tsprite_height;
\tint\tsprite_width;
\tint\tdraw_start_y;
\tint\tdraw_end_y;
\tint\tdraw_start_x;
\tint\tdraw_end_x;
}\t\t\tt_sprite_draw;

void\tsprites_render(t_game *game);
void\tsprites_update(t_game *game);
void\tsprites_sort(t_game *game);
int\t\tsprites_init(t_game *game);
void\tsprites_cleanup(t_game *game);

#endif
""")

# ============================================================================
#  src/bonus/sprite_anim.c — animation + distance sorting (4 functions)
# ============================================================================
w(f'{ROOT}/src/bonus/sprite_anim.c', header('sprite_anim.c') + """
#include "sprites.h"
#include "../graphics/graphics.h"
#include <math.h>

/* Computes squared distance from player to each sprite. */
static void\tcompute_distances(t_game *game)
{
\tt_player\t*p;
\tint\t\t\ti;
\tdouble\t\tdx;
\tdouble\t\tdy;

\tp = &game->config->player;
\ti = 0;
\twhile (i < game->num_sprites)
\t{
\t\tdx = game->sprites[i].x - p->x;
\t\tdy = game->sprites[i].y - p->y;
\t\tgame->sprites[i].distance = dx * dx + dy * dy;
\t\ti++;
\t}
}

/* Swaps two sprites in the array. */
static void\tswap_sprites(t_sprite *a, t_sprite *b)
{
\tt_sprite\ttmp;

\ttmp = *a;
\t*a = *b;
\t*b = tmp;
}

/* Sorts sprites by distance, far-to-near (so near ones draw last). */
void\tsprites_sort(t_game *game)
{
\tint\ti;
\tint\tj;
\tint\tmax_idx;

\tcompute_distances(game);
\ti = 0;
\twhile (i < game->num_sprites - 1)
\t{
\t\tmax_idx = i;
\t\tj = i + 1;
\t\twhile (j < game->num_sprites)
\t\t{
\t\t\tif (game->sprites[j].distance
\t\t\t\t> game->sprites[max_idx].distance)
\t\t\t\tmax_idx = j;
\t\t\tj++;
\t\t}
\t\tif (max_idx != i)
\t\t\tswap_sprites(&game->sprites[i], &game->sprites[max_idx]);
\t\ti++;
\t}
}

/* Updates sprite animation: cycles frame every SPRITE_ANIM_DELAY ticks. */
void\tsprites_update(t_game *game)
{
\tif (!game->has_sprites)
\t\treturn ;
\tgame->sprite_anim_counter++;
\tif (game->sprite_anim_counter >= SPRITE_ANIM_DELAY)
\t{
\t\tgame->sprite_anim_counter = 0;
\t\tgame->sprite_frame = (game->sprite_frame + 1) % SPRITE_FRAMES;
\t}
}
""")

print("sprites.h and sprite_anim.c generated.")
