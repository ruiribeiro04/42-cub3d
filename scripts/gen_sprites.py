#!/usr/bin/env python3
"""
Generate animated sprite system for cub3D (5th bonus).
- Z-buffer for wall occlusion
- Billboard sprite rendering (Lode's algorithm)
- 2-frame animation via 64x128 spritesheet (2 frames stacked)

Design:
  - Map char '2' = sprite position
  - Config line: SP ./path_to_sprite.xpm (64x128 = 2 frames of 64x64)
  - Animation: cycle frame every ~20 loop iterations
  - Z-buffer: double[WIN_WIDTH], written during wall rendering
  - Sprites sorted by distance (back-to-front) before rendering
"""

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

def rd(p):
    with open(p) as f: return f.read()
def wr(p, c):
    with open(p, 'w') as f: f.write(c)
    print(f"  patched {p}")

# ============================================================================
#  1. Patch cub3d.h — add sprite types, z_buffer, sprite fields to t_game
# ============================================================================
h = rd(f'{ROOT}/includes/cub3d.h')

# Add SPRITE_TEX_SIZE and animation constants after COLLISION_MARGIN
h = h.replace(
    "# define COLLISION_MARGIN 0.2",
    "# define COLLISION_MARGIN 0.2\n"
    "# define SPRITE_FRAMES   2\n"
    "# define SPRITE_ANIM_DELAY 20"
)

# Add t_sprite struct before t_game
h = h.replace(
    "typedef struct s_game",
    "typedef struct s_sprite\n"
    "{\n"
    "\tdouble\tx;\n"
    "\tdouble\ty;\n"
    "\tdouble\tdistance;\n"
    "}\t\t\tt_sprite;\n"
    "\n"
    "typedef struct s_game"
)

# Add sprite fields to t_game (before the closing brace)
h = h.replace(
    "\tt_keys\t\tkeys;\n"
    "}\t\t\tt_game;",
    "\tt_keys\t\tkeys;\n"
    "\tt_sprite\t*sprites;\n"
    "\tint\t\t\tnum_sprites;\n"
    "\tt_texture\tsprite_tex;\n"
    "\tint\t\t\tsprite_frame;\n"
    "\tint\t\t\tsprite_anim_counter;\n"
    "\tint\t\t\thas_sprites;\n"
    "\tdouble\t\t*z_buffer;\n"
    "}\t\t\tt_game;"
)

# Add sprite path to t_config
h = h.replace(
    "\tint\t\t\t\thas_player;\n"
    "}\t\t\tt_config;",
    "\tint\t\t\t\thas_player;\n"
    "\tchar\t\t*sprite_texture;\n"
    "\tint\t\t\t\thas_sprite;\n"
    "}\t\t\tt_config;"
)

wr(f'{ROOT}/includes/cub3d.h', h)

# ============================================================================
#  2. Patch parser_internal.h — add find_sprites + parse_sprite_line
# ============================================================================
pi = rd(f'{ROOT}/src/parser/parser_internal.h')
pi = pi.replace(
    "int\t\tflood_fill_check(t_config *cfg);",
    "int\t\tflood_fill_check(t_config *cfg);\n"
    "int\t\tfind_sprites(t_config *cfg);\n"
    "int\t\tparse_sprite_line(const char *line, t_config *cfg);"
)
wr(f'{ROOT}/src/parser/parser_internal.h', pi)

# ============================================================================
#  3. Patch parser_utils.c — accept '2' as valid map char
# ============================================================================
pu = rd(f'{ROOT}/src/parser/parser_utils.c')
pu = pu.replace(
    "int\tis_map_char(char c)\n"
    "{\n"
    "\treturn (c == '0' || c == '1' || c == 'N' || c == 'S'\n"
    "\t\t|| c == 'E' || c == 'W' || c == ' ' || c == 'D' || c == 'O');\n"
    "}",
    "int\tis_map_char(char c)\n"
    "{\n"
    "\treturn (c == '0' || c == '1' || c == 'N' || c == 'S'\n"
    "\t\t|| c == 'E' || c == 'W' || c == ' ' || c == 'D'\n"
    "\t\t|| c == 'O' || c == '2');\n"
    "}"
)
wr(f'{ROOT}/src/parser/parser_utils.c', pu)

# ============================================================================
#  4. Patch parser.c — dispatch SP lines to parse_sprite_line
# ============================================================================
pc = rd(f'{ROOT}/src/parser/parser.c')
pc = pc.replace(
    "\tif (ft_strncmp(line, \"F \", 2) == 0 || ft_strncmp(line, \"F\\t\", 2) == 0)\n"
    "\t\treturn (parse_color_line(line, cfg));\n"
    "\tif (ft_strncmp(line, \"C \", 2) == 0 || ft_strncmp(line, \"C\\t\", 2) == 0)\n"
    "\t\treturn (parse_color_line(line, cfg));",
    "\tif (ft_strncmp(line, \"F \", 2) == 0 || ft_strncmp(line, \"F\\t\", 2) == 0)\n"
    "\t\treturn (parse_color_line(line, cfg));\n"
    "\tif (ft_strncmp(line, \"C \", 2) == 0 || ft_strncmp(line, \"C\\t\", 2) == 0)\n"
    "\t\treturn (parse_color_line(line, cfg));\n"
    "\tif (ft_strncmp(line, \"SP\", 2) == 0)\n"
    "\t\treturn (parse_sprite_line(line, cfg));"
)
wr(f'{ROOT}/src/parser/parser.c', pc)

# ============================================================================
#  5. Patch free_utils.c — free sprite_texture + sprites array
# ============================================================================
fu = rd(f'{ROOT}/src/utils/free_utils.c')
fu = fu.replace(
    "\tcfg->has_player = 0;\n"
    "\tcfg->player.x = 0.0;",
    "\tcfg->has_player = 0;\n"
    "\tcfg->sprite_texture = NULL;\n"
    "\tcfg->has_sprite = 0;\n"
    "\tcfg->player.x = 0.0;"
)
fu = fu.replace(
    "\tif (config->map.grid)\n"
    "\t\tfree_str_array(config->map.grid);\n"
    "\tfree(config);",
    "\tif (config->map.grid)\n"
    "\t\tfree_str_array(config->map.grid);\n"
    "\tif (config->sprite_texture)\n"
    "\t\tfree(config->sprite_texture);\n"
    "\tfree(config);"
)
wr(f'{ROOT}/src/utils/free_utils.c', fu)

# ============================================================================
#  6. Create src/parser/parser_sprite.c — parse SP line + find_sprites
# ============================================================================
w(f'{ROOT}/src/parser/parser_sprite.c', header('parser_sprite.c') + """
#include "parser_internal.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <libft.h>

/* Verifies the sprite texture path is readable. */
static int\tverify_sprite_path(const char *path)
{
\tint\tfd;

\tfd = open(path, O_RDONLY);
\tif (fd < 0)
\t\treturn (-1);
\tclose(fd);
\treturn (0);
}

/* Parses a "SP <path>" line. Returns 0/-1. */
int\tparse_sprite_line(const char *line, t_config *cfg)
{
\tconst char\t*p;
\tchar\t\t*path;
\tsize_t\t\tlen;

\tif (cfg->has_sprite)
\t\treturn (cub_error_int("Duplicate SP identifier"));
\tif (line[2] != ' ' && line[2] != '\\t')
\t\treturn (cub_error_int("SP id must be followed by ws"));
\tp = line + 2;
\tskip_spaces(&p);
\tif (*p == '\\0')
\t\treturn (cub_error_int("Missing sprite texture path"));
\tlen = ft_strlen(p);
\twhile (len > 0 && (p[len - 1] == ' ' || p[len - 1] == '\\t'))
\t\tlen--;
\tpath = (char *)malloc(len + 1);
\tif (!path)
\t\treturn (cub_error_int("Memory allocation failed"));
\tft_strlcpy(path, p, len + 1);
\tif (verify_sprite_path(path) < 0)
\t{
\t\tcub_error("Sprite texture file cannot be opened");
\t\tfree(path);
\t\treturn (-1);
\t}
\tcfg->sprite_texture = path;
\tcfg->has_sprite = 1;
\treturn (0);
}

/* Counts '2' chars in the map grid. */
static int\tcount_sprites(t_config *cfg)
{
\tint\tx;
\tint\ty;
\tint\tcount;

\tcount = 0;
\ty = 0;
\twhile (y < cfg->map.height)
\t{
\t\tx = 0;
\t\twhile (x < cfg->map.width)
\t\t{
\t\t\tif (cfg->map.grid[y][x] == '2')
\t\t\t\tcount++;
\t\t\tx++;
\t\t}
\t\ty++;
\t}
\treturn (count);
}

/* Collects sprite positions, converts cells to '0'. Returns 0/-1. */
int\tfind_sprites(t_config *cfg)
{
\tint\tx;
\tint\ty;
\tint\tidx;

\tif (!cfg->has_sprite)
\t\treturn (0);
\tcfg->num_sprites_field = 0;
\t(void)idx;
\t(void)x;
\t(void)y;
\treturn (0);
}
""")

# Hmm, the find_sprites above is incomplete — I need to allocate and fill
# the sprites array in t_game, not t_config. But t_config doesn't have
# a sprites array. The sprites are allocated in game_init, not parse time.
# Let me restructure: find_sprites just counts and converts '2' to '0'.
# The actual sprite array allocation happens in game_init.

# Rewrite parser_sprite.c properly
w(f'{ROOT}/src/parser/parser_sprite.c', header('parser_sprite.c') + """
#include "parser_internal.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <libft.h>

/* Verifies the sprite texture path is readable. */
static int\tverify_sprite_path(const char *path)
{
\tint\tfd;

\tfd = open(path, O_RDONLY);
\tif (fd < 0)
\t\treturn (-1);
\tclose(fd);
\treturn (0);
}

/* Parses a "SP <path>" line. Returns 0/-1. */
int\tparse_sprite_line(const char *line, t_config *cfg)
{
\tconst char\t*p;
\tchar\t\t*path;
\tsize_t\t\tlen;

\tif (cfg->has_sprite)
\t\treturn (cub_error_int("Duplicate SP identifier"));
\tif (line[2] != ' ' && line[2] != '\\t')
\t\treturn (cub_error_int("SP id must be followed by ws"));
\tp = line + 2;
\tskip_spaces(&p);
\tif (*p == '\\0')
\t\treturn (cub_error_int("Missing sprite texture path"));
\tlen = ft_strlen(p);
\twhile (len > 0 && (p[len - 1] == ' ' || p[len - 1] == '\\t'))
\t\tlen--;
\tpath = (char *)malloc(len + 1);
\tif (!path)
\t\treturn (cub_error_int("Memory allocation failed"));
\tft_strlcpy(path, p, len + 1);
\tif (verify_sprite_path(path) < 0)
\t{
\t\tcub_error("Sprite texture file cannot be opened");
\t\tfree(path);
\t\treturn (-1);
\t}
\tcfg->sprite_texture = path;
\tcfg->has_sprite = 1;
\treturn (0);
}

/* Converts all '2' cells to '0' so the player can walk through them.
 * The sprite positions are collected later in game_init. */
void\tconvert_sprites_to_floor(t_config *cfg)
{
\tint\tx;
\tint\ty;

\ty = 0;
\twhile (y < cfg->map.height)
\t{
\t\tx = 0;
\t\twhile (x < cfg->map.width)
\t\t{
\t\t\tif (cfg->map.grid[y][x] == '2')
\t\t\t\tcfg->map.grid[y][x] = '0';
\t\t\tx++;
\t\t}
\t\ty++;
\t}
}
""")

# Update parser_internal.h to declare convert_sprites_to_floor
pi = rd(f'{ROOT}/src/parser/parser_internal.h')
pi = pi.replace(
    "int\t\tparse_sprite_line(const char *line, t_config *cfg);",
    "int\t\tparse_sprite_line(const char *line, t_config *cfg);\n"
    "void\tconvert_sprites_to_floor(t_config *cfg);"
)
wr(f'{ROOT}/src/parser/parser_internal.h', pi)

# ============================================================================
#  7. Patch parser_spawn.c — call convert_sprites_to_floor after find_spawn
# ============================================================================
# Actually, let's call it from finalize_map or find_spawn. Let's add it
# to the end of find_spawn in parser_spawn.c.
ps = rd(f'{ROOT}/src/parser/parser_spawn.c')
ps = ps.replace(
    "\tset_player_angle(&cfg->player);\n"
    "\tcfg->has_player = 1;\n"
    "\treturn (0);\n"
    "}",
    "\tset_player_angle(&cfg->player);\n"
    "\tcfg->has_player = 1;\n"
    "\tconvert_sprites_to_floor(cfg);\n"
    "\treturn (0);\n"
    "}"
)
wr(f'{ROOT}/src/parser/parser_spawn.c', ps)

# ============================================================================
#  8. Patch raycaster.c — write z_buffer during wall rendering
# ============================================================================
rc = rd(f'{ROOT}/src/raycaster/raycaster.c')
rc = rc.replace(
    "void\traycaster_render(t_game *game)\n"
    "{\n"
    "\tt_ray\tray;\n"
    "\tint\t\tx;\n"
    "\n"
    "\traycaster_clear(game);\n"
    "\tx = 0;\n"
    "\twhile (x < WIN_WIDTH)\n"
    "\t{\n"
    "\t\tray_init(&ray, &game->config->player, x);\n"
    "\t\tray_step(&ray, &game->config->player);\n"
    "\t\tray_dda(&ray, &game->config->map);\n"
    "\t\traycaster_draw_column(game, &ray, x);\n"
    "\t\tx++;\n"
    "\t}\n"
    "}",
    "void\traycaster_render(t_game *game)\n"
    "{\n"
    "\tt_ray\tray;\n"
    "\tint\t\tx;\n"
    "\n"
    "\traycaster_clear(game);\n"
    "\tx = 0;\n"
    "\twhile (x < WIN_WIDTH)\n"
    "\t{\n"
    "\t\tray_init(&ray, &game->config->player, x);\n"
    "\t\tray_step(&ray, &game->config->player);\n"
    "\t\tray_dda(&ray, &game->config->map);\n"
    "\t\traycaster_draw_column(game, &ray, x);\n"
    "\t\tgame->z_buffer[x] = ray.perp_wall_dist;\n"
    "\t\tx++;\n"
    "\t}\n"
    "}"
)
wr(f'{ROOT}/src/raycaster/raycaster.c', rc)

# ============================================================================
#  9. Patch graphics.h — add sprite forward declarations
# ============================================================================
gh = rd(f'{ROOT}/src/graphics/graphics.h')
gh = gh.replace(
    "int\t\thook_mouse_move(int x, int y, t_game *game);",
    "int\t\thook_mouse_move(int x, int y, t_game *game);\n"
    "void\tsprites_render(t_game *game);\n"
    "void\tsprites_update(t_game *game);\n"
    "int\t\tsprites_init(t_game *game);\n"
    "void\tsprites_cleanup(t_game *game);"
)
wr(f'{ROOT}/src/graphics/graphics.h', gh)

# ============================================================================
#  10. Patch init.c — alloc z_buffer, init sprites, load sprite texture
# ============================================================================
ic = rd(f'{ROOT}/src/graphics/init.c')
ic = ic.replace(
    "\tinit_keys(&game->keys);\n"
    "\tif (load_all_textures(game, config) < 0)\n"
    "\t\treturn (cub_error_int(\"Failed to load textures\"));\n"
    "\treturn (0);\n"
    "}",
    "\tinit_keys(&game->keys);\n"
    "\tgame->sprite_frame = 0;\n"
    "\tgame->sprite_anim_counter = 0;\n"
    "\tgame->has_sprites = 0;\n"
    "\tgame->sprites = NULL;\n"
    "\tgame->num_sprites = 0;\n"
    "\tgame->z_buffer = (double *)malloc(sizeof(double) * WIN_WIDTH);\n"
    "\tif (!game->z_buffer)\n"
    "\t\treturn (cub_error_int(\"Failed to alloc z_buffer\"));\n"
    "\tif (load_all_textures(game, config) < 0)\n"
    "\t\treturn (cub_error_int(\"Failed to load textures\"));\n"
    "\tif (config->has_sprite)\n"
    "\t{\n"
    "\t\tif (load_texture(game, &game->sprite_tex,\n"
    "\t\t\t\tconfig->sprite_texture) < 0)\n"
    "\t\t\treturn (cub_error_int(\"Failed to load sprite texture\"));\n"
    "\t\tif (sprites_init(game) < 0)\n"
    "\t\t\treturn (cub_error_int(\"Failed to init sprites\"));\n"
    "\t}\n"
    "\treturn (0);\n"
    "}"
)
wr(f'{ROOT}/src/graphics/init.c', ic)

# ============================================================================
#  11. Patch cleanup.c — free sprites + z_buffer + sprite texture
# ============================================================================
cl = rd(f'{ROOT}/src/graphics/cleanup.c')
cl = cl.replace(
    "\tif (game->frame.ptr)\n"
    "\t\tmlx_destroy_image(game->mlx, game->frame.ptr);\n"
    "\tif (game->win)\n"
    "\t\tmlx_destroy_window(game->mlx, game->win);\n"
    "\tif (game->mlx)\n"
    "\t\tmlx_destroy_display(game->mlx);",
    "\tif (game->has_sprites)\n"
    "\t\tdestroy_texture(game, &game->sprite_tex);\n"
    "\tif (game->sprites)\n"
    "\t\tfree(game->sprites);\n"
    "\tif (game->z_buffer)\n"
    "\t\tfree(game->z_buffer);\n"
    "\tif (game->frame.ptr)\n"
    "\t\tmlx_destroy_image(game->mlx, game->frame.ptr);\n"
    "\tif (game->win)\n"
    "\t\tmlx_destroy_window(game->mlx, game->win);\n"
    "\tif (game->mlx)\n"
    "\t\tmlx_destroy_display(game->mlx);"
)
wr(f'{ROOT}/src/graphics/cleanup.c', cl)

# ============================================================================
#  12. Patch hooks.c — update sprite animation + render sprites in loop
# ============================================================================
hk = rd(f'{ROOT}/src/graphics/hooks.c')
hk = hk.replace(
    "/* Main loop: process movement, render, minimap, push. */\n"
    "int\thook_loop(t_game *game)\n"
    "{\n"
    "\tplayer_update(game);\n"
    "\traycaster_render(game);\n"
    "\tminimap_draw(game);\n"
    "\tmlx_put_image_to_window(game->mlx, game->win, game->frame.ptr, 0, 0);\n"
    "\treturn (0);\n"
    "}",
    "/* Main loop: movement, render walls, sprites, minimap, push. */\n"
    "int\thook_loop(t_game *game)\n"
    "{\n"
    "\tplayer_update(game);\n"
    "\traycaster_render(game);\n"
    "\tsprites_update(game);\n"
    "\tsprites_render(game);\n"
    "\tminimap_draw(game);\n"
    "\tmlx_put_image_to_window(game->mlx, game->win, game->frame.ptr, 0, 0);\n"
    "\treturn (0);\n"
    "}"
)
wr(f'{ROOT}/src/graphics/hooks.c', hk)

print("All patches applied. Now generating sprite source files...")
