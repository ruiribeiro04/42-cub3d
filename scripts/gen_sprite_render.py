#!/usr/bin/env python3
"""Generate sprite rendering (Lode's billboard algorithm) + animation."""

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
#  src/bonus/sprites.c — billboard rendering with z-buffer (5 functions)
# ============================================================================
w(f'{ROOT}/src/bonus/sprites.c', header('sprites.c') + """
#include "sprites.h"
#include "../graphics/graphics.h"
#include <math.h>
#include <stdlib.h>

/* Computes the inverse camera matrix for sprite transformation. */
static void\tcompute_transform(t_player *p, t_sprite *s, double *inv_det,
\t\t\t\t\t\t\t\tdouble *transform_x, double *transform_y)
{
\tdouble\tsprite_x;
\tdouble\tsprite_y;
\tdouble\tdet;

\tsprite_x = s->x - p->x;
\tsprite_y = s->y - p->y;
\tdet = p->plane_x * p->dir_y - p->dir_x * p->plane_y;
\tif (det == 0)
\t\t*inv_det = 1e30;
\telse
\t\t*inv_det = 1.0 / det;
\t*transform_x = *inv_det * (p->dir_y * sprite_x - p->dir_x * sprite_y);
\t*transform_y = *inv_det * (-p->plane_y * sprite_x + p->plane_x * sprite_y);
}

/* Computes the screen X and sprite height/width. */
static void\tcompute_screen(t_sprite_draw *d, double transform_y)
{
\td->screen_x = (int)((WIN_WIDTH / 2) * (1.0 + transform_x / transform_y));
\td->sprite_height = abs((int)(WIN_HEIGHT / transform_y));
\td->draw_start_y = -d->sprite_height / 2 + WIN_HEIGHT / 2;
\tif (d->draw_start_y < 0)
\t\td->draw_start_y = 0;
\td->draw_end_y = d->sprite_height / 2 + WIN_HEIGHT / 2;
\tif (d->draw_end_y >= WIN_HEIGHT)
\t\td->draw_end_y = WIN_HEIGHT - 1;
\td->sprite_width = abs((int)(WIN_HEIGHT / transform_y));
\td->draw_start_x = -d->sprite_width / 2 + d->screen_x;
\tif (d->draw_start_x < 0)
\t\td->draw_start_x = 0;
\td->draw_end_x = d->sprite_width / 2 + d->screen_x;
\tif (d->draw_end_x >= WIN_WIDTH)
\t\td->draw_end_x = WIN_WIDTH - 1;
}

/* Draws one vertical stripe of a sprite. */
static void\tdraw_stripe(t_game *game, t_sprite_draw *d,
\t\t\t\t\t\tint stripe, double transform_y)
{
\tint\t\t\ty;
\tint\t\t\ttex_x;
\tint\t\t\ttex_y;
\tint\t\t\tcolor;
\tint\t\t\tframe_offset;
\tt_texture\t*tex;

\ttex = &game->sprite_tex;
\ttex_x = (int)((256 * (stripe - (-d->sprite_width / 2 + d->screen_x))
\t\t\t* TEX_SIZE / d->sprite_width) / 256);
\tframe_offset = game->sprite_frame * TEX_SIZE;
\ty = d->draw_start_y;
\twhile (y < d->draw_end_y)
\t{
\t\ttex_y = (((y * 256 - WIN_HEIGHT * 128 + d->sprite_height * 128)
\t\t\t\t/ d->sprite_height) / 256) + frame_offset;
\t\tif (tex_y >= 0 && tex_y < (TEX_SIZE * SPRITE_FRAMES)
\t\t\t&& tex_x >= 0 && tex_x < TEX_SIZE)
\t\t{
\t\t\tcolor = tex->pixels[tex_y * TEX_SIZE + tex_x];
\t\t\tif ((color & 0x00FFFFFF) != 0 && transform_y > 0
\t\t\t\t&& transform_y < game->z_buffer[stripe])
\t\t\t\tframe_put_pixel(game, stripe, y, color);
\t\t}
\t\ty++;
\t}
}

/* Renders all visible sprites, sorted back-to-front. */
void\tsprites_render(t_game *game)
{
\tt_sprite_draw\td;
\tdouble\t\t\tinv_det;
\tdouble\t\t\ttx;
\tdouble\t\t\tty;
\tint\t\t\t\ti;
\tint\t\t\t\tstripe;

\tif (!game->has_sprites)
\t\treturn ;
\tsprites_sort(game);
\ti = 0;
\twhile (i < game->num_sprites)
\t{
\t\tcompute_transform(&game->config->player,
\t\t\t&game->sprites[i], &inv_det, &tx, &ty);
\t\tif (ty > 0)
\t\t{
\t\t\tcompute_screen(&d, ty);
\t\t\tstripe = d.draw_start_x;
\t\t\twhile (stripe < d.draw_end_x)
\t\t\t{
\t\t\t\tdraw_stripe(game, &d, stripe, ty);
\t\t\t\tstripe++;
\t\t\t}
\t\t}
\t\ti++;
\t}
}
""")

# Hmm, I used t_sprite_draw which I haven't defined. Let me add it to sprites.h.
# Also I referenced sprites_sort which needs to be defined.

print("sprites.c generated (needs t_sprite_draw + sprites_sort)")
