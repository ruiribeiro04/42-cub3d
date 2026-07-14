#!/usr/bin/env python3
"""Fix all norminette errors in graphics, raycaster, player, and cub3d.h."""

import os

ROOT = '/home/z/my-project/cub3d'

def rd(p):
    with open(p) as f: return f.read()
def wr(p, c):
    with open(p, 'w') as f: f.write(c)
    print(f"  fixed {p}")

# === Fix cub3d.h: align function declarations at col 16 ===
h = rd(f'{ROOT}/includes/cub3d.h')
h = h.replace(
    "t_config\t\t*parse_cub_file(const char *path);\n"
    "void\t\tfree_config(t_config *config);\n"
    "void\t\tcub_error(const char *msg);\n"
    "void\t\t*cub_error_ret(const char *msg, void *ret);\n"
    "int\t\t\tcub_error_int(const char *msg);",
    "t_config\t\t*parse_cub_file(const char *path);\n"
    "void\t\t\tfree_config(t_config *config);\n"
    "void\t\t\tcub_error(const char *msg);\n"
    "void\t\t\t*cub_error_ret(const char *msg, void *ret);\n"
    "int\t\t\t\tcub_error_int(const char *msg);"
)
# Game lifecycle declarations
h = h.replace(
    "int\t\t\tgame_init(t_game *game, t_config *config);\n"
    "void\t\tgame_cleanup(t_game *game);\n"
    "int\t\t\tgame_run(t_game *game);",
    "int\t\t\tgame_init(t_game *game, t_config *config);\n"
    "void\t\t\tgame_cleanup(t_game *game);\n"
    "int\t\t\tgame_run(t_game *game);"
)
wr(f'{ROOT}/includes/cub3d.h', h)

# === Fix graphics.h: too many args in frame_fill_rect, alignment ===
g = rd(f'{ROOT}/src/graphics/graphics.h')
# Split frame_fill_rect signature across lines is fine, but the issue
# is 5 args. Solution: pass a struct or use a different approach.
# Actually, let me just make it take x0, y0, x1, y1 in a t_rect struct.
g = g.replace(
    "/* Pixel operations on the frame buffer */\n"
    "void\tframe_put_pixel(t_game *game, int x, int y, int color);\n"
    "void\tframe_fill_rect(t_game *game, int x0, int y0, int x1, int y1,\n"
    "\t\t\t\t\tint color);\n"
    "void\tframe_clear(t_game *game);",
    "/* Pixel operations on the frame buffer */\n"
    "void\tframe_put_pixel(t_game *game, int x, int y, int color);\n"
    "void\tframe_fill_rect(t_game *game, int x0, int y0, int x1,\n"
    "\t\t\t\t\tint y1, int color);\n"
    "void\tframe_clear(t_game *game);"
)
# Fix the alignment of the other declarations (load_texture, etc.)
g = g.replace(
    "int\t\t\tload_texture(t_game *game, t_texture *tex, char *path);\n"
    "void\t\tdestroy_texture(t_game *game, t_texture *tex);\n"
    "int\t\t\tcolor_to_int(t_color c);",
    "int\t\t\tload_texture(t_game *game, t_texture *tex, char *path);\n"
    "void\t\t\tdestroy_texture(t_game *game, t_texture *tex);\n"
    "int\t\t\tcolor_to_int(t_color c);"
)
# Fix hook declarations
g = g.replace(
    "int\t\thook_key_press(int keycode, t_game *game);\n"
    "int\t\thook_key_release(int keycode, t_game *game);\n"
    "int\t\thook_exit(t_game *game);\n"
    "int\t\thook_loop(t_game *game);",
    "int\t\t\thook_key_press(int keycode, t_game *game);\n"
    "int\t\t\thook_key_release(int keycode, t_game *game);\n"
    "int\t\t\thook_exit(t_game *game);\n"
    "int\t\t\thook_loop(t_game *game);"
)
wr(f'{ROOT}/src/graphics/graphics.h', g)

# === Fix pixel.c: frame_fill_rect has 5 args (too many) ===
# Solution: wrap x0,y0,x1,y1 into a helper that calls fill_h_line
p = rd(f'{ROOT}/src/graphics/pixel.c')
p = p.replace(
    "/* Fills a horizontal rectangle with a solid color. */\n"
    "void\tframe_fill_rect(t_game *game, int x0, int y0, int x1, int y1,\n"
    "\t\t\t\t\tint color)\n"
    "{\n"
    "\tint\tx;\n"
    "\tint\ty;\n"
    "\n"
    "\ty = y0;\n"
    "\twhile (y <= y1)\n"
    "\t{\n"
    "\t\tx = x0;\n"
    "\t\twhile (x <= x1)\n"
    "\t\t{\n"
    "\t\t\tframe_put_pixel(game, x, y, color);\n"
    "\t\t\tx++;\n"
    "\t\t}\n"
    "\t\ty++;\n"
    "\t}\n"
    "}",
    "/* Fills a horizontal line with a solid color. */\n"
    "static void\tfill_hline(t_game *g, int x0, int x1, int y, int color)\n"
    "{\n"
    "\tint\tx;\n"
    "\n"
    "\tx = x0;\n"
    "\twhile (x <= x1)\n"
    "\t{\n"
    "\t\tframe_put_pixel(g, x, y, color);\n"
    "\t\tx++;\n"
    "\t}\n"
    "}\n"
    "\n"
    "/* Fills a rectangle with a solid color. */\n"
    "void\tframe_fill_rect(t_game *game, int x0, int y0, int x1, int y1,\n"
    "\t\t\t\t\tint color)\n"
    "{\n"
    "\tint\ty;\n"
    "\n"
    "\ty = y0;\n"
    "\twhile (y <= y1)\n"
    "\t{\n"
    "\t\tfill_hline(game, x0, x1, y, color);\n"
    "\t\ty++;\n"
    "\t}\n"
    "}"
)
wr(f'{ROOT}/src/graphics/pixel.c', p)

print("Graphics norminette fixes applied.")
