#!/usr/bin/env python3
"""Generate remaining parser .c files and fix the header."""

import os

ROOT = '/home/z/my-project/cub3d'

def header(name, login='ruiferna', mail='ruiferna@student.42porto.com'):
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
    with open(path, 'w') as f:
        f.write(content)
    print(f"  wrote {path}")

# ============================================================================
#  Update parser_internal.h to add finalize_map declaration
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
/*  MAP COLLECTOR                                                              */
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
int\t\tfinalize_map(t_config *cfg, t_map_collector *c);

/* ========================================================================== */
/*  SECTION PARSERS                                                            */
/* ========================================================================== */

int\t\tparse_texture_line(const char *line, t_config *cfg);
int\t\tparse_color_line(const char *line, t_config *cfg);
int\t\tparse_map_block(int fd, char *first_line, t_config *cfg);

/* ========================================================================== */
/*  VALIDATION                                                                 */
/* ========================================================================== */

int\t\tvalidate_config(t_config *cfg);
int\t\tfind_spawn(t_config *cfg);
int\t\tflood_fill_check(t_config *cfg);

/* ========================================================================== */
/*  FREE HELPERS                                                               */
/* ========================================================================== */

void\tfree_str_array(char **arr);
t_config\t*alloc_config(void);

#endif
""")

# ============================================================================
#  src/parser/parser_spawn.c  (3 functions)
# ============================================================================
write_file(f'{ROOT}/src/parser/parser_spawn.c', header('parser_spawn.c') + """
#include "parser_internal.h"

/* Returns 1 if c is a spawn char (N/S/E/W). */
static int\tis_spawn_char(char c)
{
\treturn (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/* Sets player angle from direction. 0=E, PI/2=S, PI=W, 3PI/2=N. */
static void\tset_player_angle(t_player *p)
{
\tif (p->direction == 'E')
\t\tp->angle = 0.0;
\telse if (p->direction == 'S')
\t\tp->angle = PI / 2.0;
\telse if (p->direction == 'W')
\t\tp->angle = PI;
\telse if (p->direction == 'N')
\t\tp->angle = 3.0 * PI / 2.0;
}

/* Scans map for spawn (exactly one of N/S/E/W). Records pos
 * and direction, replaces cell with '0'. Returns 0/-1. */
int\tfind_spawn(t_config *cfg)
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
\t\t\tif (is_spawn_char(cfg->map.grid[y][x]))
\t\t\t{
\t\t\t\tcount++;
\t\t\t\tif (count > 1)
\t\t\t\t\treturn (cub_error_ret_count());
\t\t\t\tcfg->player.x = (double)x;
\t\t\t\tcfg->player.y = (double)y;
\t\t\t\tcfg->player.direction = cfg->map.grid[y][x];
\t\t\t\tcfg->map.grid[y][x] = '0';
\t\t\t}
\t\t\tx++;
\t\t}
\t\ty++;
\t}
\tif (count == 0)
\t{
\t\tcub_error("No player spawn found in map");
\t\treturn (-1);
\t}
\tset_player_angle(&cfg->player);
\tcfg->has_player = 1;
\treturn (0);
}
""")

# Hmm, I used a non-existent helper cub_error_ret_count(). Let me fix.
# Actually, let me rewrite this to avoid the helper.

write_file(f'{ROOT}/src/parser/parser_spawn.c', header('parser_spawn.c') + """
#include "parser_internal.h"

/* Returns 1 if c is a spawn char (N/S/E/W). */
static int\tis_spawn_char(char c)
{
\treturn (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/* Sets player angle from direction. 0=E, PI/2=S, PI=W, 3PI/2=N. */
static void\tset_player_angle(t_player *p)
{
\tif (p->direction == 'E')
\t\tp->angle = 0.0;
\telse if (p->direction == 'S')
\t\tp->angle = PI / 2.0;
\telse if (p->direction == 'W')
\t\tp->angle = PI;
\telse if (p->direction == 'N')
\t\tp->angle = 3.0 * PI / 2.0;
}

/* Scans map for spawn (exactly one of N/S/E/W). Records pos
 * and direction, replaces cell with '0'. Returns 0/-1. */
int\tfind_spawn(t_config *cfg)
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
\t\t\tif (is_spawn_char(cfg->map.grid[y][x]))
\t\t\t{
\t\t\t\tcount++;
\t\t\t\tif (count > 1)
\t\t\t\t{
\t\t\t\t\tcub_error("Multiple player spawns in map");
\t\t\t\t\treturn (-1);
\t\t\t\t}
\t\t\t\tcfg->player.x = (double)x;
\t\t\t\tcfg->player.y = (double)y;
\t\t\t\tcfg->player.direction = cfg->map.grid[y][x];
\t\t\t\tcfg->map.grid[y][x] = '0';
\t\t\t}
\t\t\tx++;
\t\t}
\t\ty++;
\t}
\tif (count == 0)
\t{
\t\tcub_error("No player spawn found in map");
\t\treturn (-1);
\t}
\tset_player_angle(&cfg->player);
\tcfg->has_player = 1;
\treturn (0);
}
""")

# ============================================================================
#  src/parser/parser_flood_fill.c  (3 functions)
# ============================================================================
write_file(f'{ROOT}/src/parser/parser_flood_fill.c', header('parser_flood_fill.c') + """
#include "parser_internal.h"
#include <stdlib.h>
#include <libft.h>

/* BFS context bundling everything explore() needs. */
typedef struct s_flood_ctx
{
\tt_config\t*cfg;
\tchar\t\t*visited;
\tint\t\t\t*queue;
\tint\t\t\tq_tail;
}\tt_flood_ctx;

/* Visits (x,y). Wall/visited -> 0. Void/oob -> -1 (leak).
 * Otherwise marks visited and pushes to queue. */
static int\texplore(t_flood_ctx *ctx, int x, int y)
{
\tint\tidx;
\tint\tcell;

\tif (x < 0 || x >= ctx->cfg->map.width)
\t\treturn (-1);
\tif (y < 0 || y >= ctx->cfg->map.height)
\t\treturn (-1);
\tidx = y * ctx->cfg->map.width + x;
\tif (ctx->visited[idx])
\t\treturn (0);
\tcell = ctx->cfg->map.grid[y][x];
\tif (cell == '1')
\t\treturn (0);
\tif (cell == ' ')
\t\treturn (-1);
\tctx->visited[idx] = 1;
\tctx->queue[ctx->q_tail++] = idx;
\treturn (0);
}

/* Iterative BFS from (sx, sy). 0 if enclosed, -1 if leak. */
static int\tflood_fill_iter(t_config *cfg, char *visited, int sx, int sy)
{
\tt_flood_ctx\tctx;
\tint\t\t\tq_head;
\tint\t\t\tidx;
\tint\t\t\tx;
\tint\t\t\ty;

\tctx.cfg = cfg;
\tctx.visited = visited;
\tctx.q_tail = 0;
\tctx.queue = (int *)malloc(sizeof(int) * (cfg->map.height * cfg->map.width));
\tif (!ctx.queue)
\t\treturn (-1);
\tq_head = 0;
\tidx = sy * cfg->map.width + sx;
\tctx.queue[ctx.q_tail++] = idx;
\tvisited[idx] = 1;
\twhile (q_head < ctx.q_tail)
\t{
\t\tidx = ctx.queue[q_head++];
\t\tx = idx % cfg->map.width;
\t\ty = idx / cfg->map.width;
\t\tif (explore(&ctx, x + 1, y) < 0 || explore(&ctx, x - 1, y) < 0
\t\t\t|| explore(&ctx, x, y + 1) < 0 || explore(&ctx, x, y - 1) < 0)
\t\t{
\t\t\tfree(ctx.queue);
\t\t\treturn (-1);
\t\t}
\t}
\tfree(ctx.queue);
\treturn (0);
}

/* Allocates visited array, runs flood fill, frees. */
int\tflood_fill_check(t_config *cfg)
{
\tchar\t*visited;
\tint\t\tresult;
\tint\t\tmap_size;

\tmap_size = cfg->map.height * cfg->map.width;
\tvisited = (char *)malloc((size_t)map_size);
\tif (!visited)
\t{
\t\tcub_error("Memory allocation failed");
\t\treturn (-1);
\t}
\tft_bzero(visited, (size_t)map_size);
\tresult = flood_fill_iter(cfg, visited,
\t\t\t(int)cfg->player.x, (int)cfg->player.y);
\tfree(visited);
\tif (result < 0)
\t{
\t\tcub_error("Map is not closed (player can escape)");
\t\treturn (-1);
\t}
\treturn (0);
}
""")

# ============================================================================
#  src/parser/parser_validate.c  (2 functions)
# ============================================================================
write_file(f'{ROOT}/src/parser/parser_validate.c', header('parser_validate.c') + """
#include "parser_internal.h"

/* If !present, prints `name` error. Returns 0/-1. */
static int\tcheck_missing(int present, const char *name)
{
\tif (!present)
\t{
\t\tcub_error(name);
\t\treturn (-1);
\t}
\treturn (0);
}

/* Verifies every required element is present in cfg. */
int\tvalidate_config(t_config *cfg)
{
\tif (check_missing(cfg->has_north, "Missing NO texture") < 0
\t\t|| check_missing(cfg->has_south, "Missing SO texture") < 0
\t\t|| check_missing(cfg->has_west, "Missing WE texture") < 0
\t\t|| check_missing(cfg->has_east, "Missing EA texture") < 0
\t\t|| check_missing(cfg->has_floor, "Missing F color") < 0
\t\t|| check_missing(cfg->has_ceiling, "Missing C color") < 0
\t\t|| check_missing(cfg->has_player, "Missing player spawn") < 0)
\t\treturn (-1);
\treturn (0);
}
""")

# ============================================================================
#  Also fix parser_map.c (typo tc -> c)
# ============================================================================
write_file(f'{ROOT}/src/parser/parser_map.c', header('parser_map.c') + """
#include "parser_internal.h"
#include <stdlib.h>
#include <libft.h>

/* Grows the collector's lines array. Returns 0/-1. */
static int\tcollector_grow(t_map_collector *c)
{
\tchar\t**new_lines;
\tint\t\tnew_cap;
\tint\t\ti;

\tnew_cap = c->capacity * 2;
\tnew_lines = (char **)malloc(sizeof(char *) * new_cap);
\tif (!new_lines)
\t{
\t\tcub_error("Memory allocation failed");
\t\treturn (-1);
\t}
\ti = 0;
\twhile (i < c->count)
\t{
\t\tnew_lines[i] = c->lines[i];
\t\ti++;
\t}
\tfree(c->lines);
\tc->lines = new_lines;
\tc->capacity = new_cap;
\treturn (0);
}

/* Initializes collector with first_line. Takes ownership. */
int\tcollector_init(t_map_collector *c, char *first_line)
{
\tc->capacity = 16;
\tc->lines = (char **)malloc(sizeof(char *) * c->capacity);
\tif (!c->lines)
\t{
\t\tcub_error("Memory allocation failed");
\t\tfree(first_line);
\t\treturn (-1);
\t}
\tc->lines[0] = first_line;
\tc->count = 1;
\tc->max_width = 0;
\tif (first_line)
\t\tc->max_width = (int)ft_strlen(first_line);
\treturn (0);
}

/* Appends line. Takes ownership. Returns 0/-1. */
int\tcollector_add(t_map_collector *c, char *line)
{
\tint\tline_len;

\tif (c->count >= c->capacity)
\t{
\t\tif (collector_grow(c) < 0)
\t\t{
\t\t\tfree(line);
\t\t\treturn (-1);
\t\t}
\t}
\tc->lines[c->count] = line;
\tline_len = (int)ft_strlen(line);
\tif (line_len > c->max_width)
\t\tc->max_width = line_len;
\tc->count++;
\treturn (0);
}

/* Frees all lines and the array. NULL-safe. */
void\tcollector_free(t_map_collector *c)
{
\tint\ti;

\tif (!c->lines)
\t\treturn ;
\ti = 0;
\twhile (i < c->count)
\t{
\t\tfree(c->lines[i]);
\t\ti++;
\t}
\tfree(c->lines);
\tc->lines = NULL;
}

/* Reads every remaining line of fd and assembles the map. */
int\tparse_map_block(int fd, char *first_line, t_config *cfg)
{
\tt_map_collector\tc;
\tchar\t\t\t*line;

\tif (collector_init(&c, first_line) < 0)
\t\treturn (-1);
\tline = get_next_line(fd);
\twhile (line != NULL)
\t{
\t\tstrip_newline(line);
\t\tif (validate_map_line(line) < 0)
\t\t{
\t\t\tfree(line);
\t\t\tcollector_free(&c);
\t\t\treturn (-1);
\t\t}
\t\tif (collector_add(&c, line) < 0)
\t\t{
\t\t\tcollector_free(&c);
\t\t\treturn (-1);
\t\t}
\t\tline = get_next_line(fd);
\t}
\treturn (finalize_map(cfg, &c));
}
""")

# ============================================================================
#  Also fix parser_map_helpers.c (add free_grid_partial)
# ============================================================================
write_file(f'{ROOT}/src/parser/parser_map_helpers.c', header('parser_map_helpers.c') + """
#include "parser_internal.h"
#include <stdlib.h>
#include <libft.h>

/* Returns 0 if every char in line is a valid map char. */
int\tvalidate_map_line(const char *line)
{
\tint\ti;

\ti = 0;
\twhile (line[i] != '\\0')
\t{
\t\tif (!is_map_char(line[i]))
\t\t{
\t\t\tcub_error("Invalid character in map");
\t\t\treturn (-1);
\t\t}
\t\ti++;
\t}
\treturn (0);
}

/* Allocates new string of `width`, copying src + padding. */
char\t*pad_line(const char *src, int width)
{
\tchar\t*dst;
\tint\t\tsrc_len;
\tint\t\ti;

\tdst = (char *)malloc(sizeof(char) * (width + 1));
\tif (!dst)
\t\treturn (NULL);
\tsrc_len = (int)ft_strlen(src);
\ti = 0;
\twhile (i < src_len && i < width)
\t{
\t\tdst[i] = src[i];
\t\ti++;
\t}
\twhile (i < width)
\t{
\t\tdst[i] = ' ';
\t\ti++;
\t}
\tdst[width] = '\\0';
\treturn (dst);
}

/* Frees grid[0..count-1] and grid itself, then collector. */
static void\tfree_grid_partial(char **grid, int count, t_map_collector *c)
{
\tint\ti;

\ti = 0;
\twhile (i < count)
\t{
\t\tfree(grid[i]);
\t\ti++;
\t}
\tfree(grid);
\tcollector_free(c);
}

/* Allocates grid, pads each line, finds spawn, flood fill. */
int\tfinalize_map(t_config *cfg, t_map_collector *c)
{
\tchar\t**grid;
\tint\t\ti;

\tif (c->count == 0)
\t{
\t\tcub_error("No map found");
\t\tcollector_free(c);
\t\treturn (-1);
\t}
\tgrid = (char **)malloc(sizeof(char *) * (c->count + 1));
\tif (!grid)
\t{
\t\tcub_error("Memory allocation failed");
\t\tcollector_free(c);
\t\treturn (-1);
\t}
\ti = 0;
\twhile (i < c->count)
\t{
\t\tgrid[i] = pad_line(c->lines[i], c->max_width);
\t\tif (!grid[i])
\t\t{
\t\t\tcub_error("Memory allocation failed");
\t\t\tfree_grid_partial(grid, i, c);
\t\t\treturn (-1);
\t\t}
\t\ti++;
\t}
\tgrid[c->count] = NULL;
\tcfg->map.grid = grid;
\tcfg->map.height = c->count;
\tcfg->map.width = c->max_width;
\tcollector_free(c);
\tif (find_spawn(cfg) < 0)
\t\treturn (-1);
\treturn (flood_fill_check(cfg));
}
""")

print("All remaining parser files generated.")
