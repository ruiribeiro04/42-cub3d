#!/usr/bin/env python3
"""
Regenerate all cub3D parser source files with norminette-compliant formatting.
- Tabs for indentation and alignment (not spaces)
- Comments <= 80 chars per line
- Max 5 functions per .c file
- Max 25 lines per function body
- Max 4 arguments per function
- No typedefs in .c files (moved to header)
"""

import os

ROOT = '/home/z/my-project/cub3d'

def header(name, login='ruiferna', mail='ruiferna@student.42porto.com'):
    """Generate the 42 file header (uses spaces, not tabs, for alignment)."""
    return f"""/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   {name:<50}:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: {mail:<50}+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by {login:<16}#+#    #+#             */
/*   Updated: 2025/07/11 10:00:00 by {login:<16}###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
"""

def write_file(path, content):
    """Write content to file, ensuring the directory exists."""
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, 'w') as f:
        f.write(content)
    print(f"  wrote {path} ({len(content)} bytes)")

# ============================================================================
#  includes/cub3d.h
# ============================================================================
write_file(f'{ROOT}/includes/cub3d.h', header('cub3d.h') + """
#ifndef CUB3D_H
# define CUB3D_H

# include <stddef.h>

# ifndef PI
#  define PI 3.14159265358979323846
# endif

/* ========================================================================== */
/*  TYPES                                                                      */
/* ========================================================================== */

/* RGB color. Each channel in [0, 255]. */
typedef struct s_color
{
\tint\tr;
\tint\tg;
\tint\tb;
}\tt_color;

/* Filesystem paths to the four wall textures. Heap-allocated. */
typedef struct s_texture_paths
{
\tchar\t*north;
\tchar\t*south;
\tchar\t*west;
\tchar\t*east;
}\tt_texture_paths;

/* Player spawn state parsed from the map. */
typedef struct s_player
{
\tdouble\tx;
\tdouble\ty;
\tchar\tdirection;
\tdouble\tangle;
}\tt_player;

/* The map grid. `grid` is NULL-terminated. Each row is padded with
 * spaces to `width` chars so the grid is rectangular. */
typedef struct s_map
{
\tchar\t**grid;
\tint\t\theight;
\tint\t\twidth;
}\tt_map;

/* Full scene configuration parsed from a .cub file. */
typedef struct s_config
{
\tt_texture_paths\ttextures;
\tt_color\t\t\tfloor;
\tt_color\t\t\tceiling;
\tt_map\t\t\tmap;
\tt_player\t\tplayer;
\tint\t\t\t\thas_north;
\tint\t\t\t\thas_south;
\tint\t\t\t\thas_west;
\tint\t\t\t\thas_east;
\tint\t\t\t\thas_floor;
\tint\t\t\t\thas_ceiling;
\tint\t\t\t\thas_player;
}\tt_config;

/* ========================================================================== */
/*  PARSER (public API)                                                        */
/* ========================================================================== */

/* Parses a .cub scene file. Returns a freshly-allocated t_config
 * on success. On failure, prints "Error\\n" + msg to stderr and
 * returns NULL. Caller must free with free_config(). */
t_config\t\t*parse_cub_file(const char *path);

/* Frees every heap field of `config` and the struct itself. NULL-safe. */
void\t\tfree_config(t_config *config);

/* ========================================================================== */
/*  ERROR HANDLING                                                             */
/* ========================================================================== */

/* Prints "Error\\n" followed by `msg` to stderr. Does not exit. */
void\t\tcub_error(const char *msg);

/* Convenience: prints error then returns `ret` (typically NULL). */
void\t\t*cub_error_ret(const char *msg, void *ret);

#endif
""")

# ============================================================================
#  src/parser/parser_internal.h
# ============================================================================
write_file(f'{ROOT}/src/parser/parser_internal.h', header('parser_internal.h') + """
#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

# include "cub3d.h"

/* Forward declaration (do not pull <libft.h> here). */
char\t*get_next_line(int fd);

/* ========================================================================== */
/*  LINE CLASSIFICATION                                                        */
/* ========================================================================== */

int\t\tis_blank_line(const char *line);
int\t\tlooks_like_map(const char *line);
void\tskip_spaces(const char **p);
int\t\tis_map_char(char c);
void\tstrip_newline(char *line);
void\tdrain_fd(int fd);

/* ========================================================================== */
/*  MAP COLLECTOR (used by parser_map*.c)                                      */
/* ========================================================================== */

typedef struct s_map_collector
{
\tchar\t**lines;
\tint\t\tcount;
\tint\t\tcapacity;
\tint\t\tmax_width;
}\tt_map_collector;

int\t\tcollector_init(t_map_collector *c, char *first_line);
int\t\tcollector_add(t_map_collector *c, char *line);
void\tcollector_free(t_map_collector *c);
int\t\tvalidate_map_line(const char *line);
char\t*pad_line(const char *src, int width);

/* ========================================================================== */
/*  SECTION PARSERS                                                            */
/* ========================================================================== */

int\t\tparse_texture_line(const char *line, t_config *config);
int\t\tparse_color_line(const char *line, t_config *config);
int\t\tparse_map_block(int fd, char *first_line, t_config *config);

/* ========================================================================== */
/*  VALIDATION                                                                 */
/* ========================================================================== */

int\t\tvalidate_config(t_config *config);
int\t\tfind_spawn(t_config *config);
int\t\tflood_fill_check(t_config *config);

/* ========================================================================== */
/*  FREE HELPERS                                                               */
/* ========================================================================== */

void\tfree_str_array(char **arr);
t_config\t*alloc_config(void);

#endif
""")

print("Headers generated.")
