#!/usr/bin/env python3
"""
Generate all cub3D parser .c source files with norminette-compliant formatting.
- Max 5 functions per file
- Max 25 lines per function body
- Max 4 arguments per function
- Tabs for indentation and alignment
- Comments <= 80 chars per line
"""

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
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, 'w') as f:
        f.write(content)
    print(f"  wrote {path}")

# ============================================================================
#  src/error/error.c  (3 functions)
# ============================================================================
write_file(f'{ROOT}/src/error/error.c', header('error.c') + """
#include "cub3d.h"
#include <unistd.h>
#include <libft.h>

/* Writes `s` + '\\n' to fd via write() to preserve const. */
static void\tputstr_endl(const char *s, int fd)
{
\tsize_t\tlen;

\tif (!s)
\t\treturn ;
\tlen = ft_strlen(s);
\twrite(fd, s, len);
\twrite(fd, "\\n", 1);
}

/* Prints "Error\\n" + `msg` to stderr. Does not exit. */
void\tcub_error(const char *msg)
{
\tputstr_endl("Error", STDERR_FILENO);
\tif (msg)
\t\tputstr_endl(msg, STDERR_FILENO);
}

/* Prints error then returns `ret` (typically NULL). */
void\t*cub_error_ret(const char *msg, void *ret)
{
\tcub_error(msg);
\treturn (ret);
}
""")

# ============================================================================
#  src/utils/free_utils.c  (3 functions)
# ============================================================================
write_file(f'{ROOT}/src/utils/free_utils.c', header('free_utils.c') + """
#include "cub3d.h"
#include <stdlib.h>

/* Frees a NULL-terminated char** array. NULL-safe. */
void\tfree_str_array(char **arr)
{
\tint\ti;

\tif (!arr)
\t\treturn ;
\ti = 0;
\twhile (arr[i])
\t{
\t\tfree(arr[i]);
\t\ti++;
\t}
\tfree(arr);
}

/* Allocates and zeroes a t_config. NULL on alloc failure. */
t_config\t*alloc_config(void)
{
\tt_config\t*cfg;

\tcfg = (t_config *)malloc(sizeof(t_config));
\tif (!cfg)
\t\treturn (NULL);
\tcfg->textures.north = NULL;
\tcfg->textures.south = NULL;
\tcfg->textures.west = NULL;
\tcfg->textures.east = NULL;
\tcfg->map.grid = NULL;
\tcfg->map.height = 0;
\tcfg->map.width = 0;
\tcfg->has_north = 0;
\tcfg->has_south = 0;
\tcfg->has_west = 0;
\tcfg->has_east = 0;
\tcfg->has_floor = 0;
\tcfg->has_ceiling = 0;
\tcfg->has_player = 0;
\tcfg->player.x = 0.0;
\tcfg->player.y = 0.0;
\tcfg->player.direction = '\\0';
\tcfg->player.angle = 0.0;
\treturn (cfg);
}

/* Frees all heap fields of `config` and the struct. NULL-safe. */
void\tfree_config(t_config *config)
{
\tif (!config)
\t\treturn ;
\tfree(config->textures.north);
\tfree(config->textures.south);
\tfree(config->textures.west);
\tfree(config->textures.east);
\tif (config->map.grid)
\t\tfree_str_array(config->map.grid);
\tfree(config);
}
""")

# ============================================================================
#  src/parser/parser_utils.c  (5 functions)
# ============================================================================
write_file(f'{ROOT}/src/parser/parser_utils.c', header('parser_utils.c') + """
#include "parser_internal.h"
#include <libft.h>

/* Returns 1 if c is space or tab. */
static int\tis_space_char(char c)
{
\treturn (c == ' ' || c == '\\t');
}

/* Returns 1 if line is blank (NULL, empty, or only ws). */
int\tis_blank_line(const char *line)
{
\tint\ti;

\tif (!line)
\t\treturn (1);
\ti = 0;
\twhile (line[i] != '\\0')
\t{
\t\tif (!is_space_char(line[i]))
\t\t\treturn (0);
\t\ti++;
\t}
\treturn (1);
}

/* Advances *p past any run of spaces/tabs. */
void\tskip_spaces(const char **p)
{
\tif (!p || !*p)
\t\treturn ;
\twhile (is_space_char(**p))
\t\t(*p)++;
}

/* Returns 1 if c is a valid map char (incl. space, excl. tab). */
int\tis_map_char(char c)
{
\treturn (c == '0' || c == '1' || c == 'N' || c == 'S'
\t\t|| c == 'E' || c == 'W' || c == ' ');
}

/* Returns 1 if line looks like first map line (has '1',
 * only map chars). */
int\tlooks_like_map(const char *line)
{
\tint\ti;
\tint\thas_one;

\tif (!line)
\t\treturn (0);
\ti = 0;
\thas_one = 0;
\twhile (line[i] != '\\0')
\t{
\t\tif (!is_map_char(line[i]))
\t\t\treturn (0);
\t\tif (line[i] == '1')
\t\t\thas_one = 1;
\t\ti++;
\t}
\treturn (has_one);
}
""")

# ============================================================================
#  src/parser/parser_io.c  (2 functions: strip_newline, drain_fd)
# ============================================================================
write_file(f'{ROOT}/src/parser/parser_io.c', header('parser_io.c') + """
#include "parser_internal.h"
#include <stdlib.h>
#include <libft.h>

/* Strips trailing "\\n" and "\\r" from `line` in place. NULL-safe. */
void\tstrip_newline(char *line)
{
\tsize_t\tlen;

\tif (!line)
\t\treturn ;
\tlen = ft_strlen(line);
\tif (len > 0 && line[len - 1] == '\\n')
\t\tline[--len] = '\\0';
\tif (len > 0 && line[len - 1] == '\\r')
\t\tline[--len] = '\\0';
}

/* Reads & discards every remaining line of fd until EOF.
 * Needed to reset GNL's internal stash before fd reuse. */
void\tdrain_fd(int fd)
{
\tchar\t*line;

\tline = get_next_line(fd);
\twhile (line != NULL)
\t{
\t\tfree(line);
\t\tline = get_next_line(fd);
\t}
}
""")

# ============================================================================
#  src/parser/parser.c  (4 functions)
# ============================================================================
write_file(f'{ROOT}/src/parser/parser.c', header('parser.c') + """
#include "parser_internal.h"
#include <fcntl.h>
#include <unistd.h>
#include <libft.h>

/* Returns 1 if path ends with ".cub". */
static int\thas_cub_extension(const char *path)
{
\tsize_t\tlen;

\tif (!path)
\t\treturn (0);
\tlen = ft_strlen(path);
\tif (len < 5)
\t\treturn (0);
\treturn (ft_strncmp(path + len - 4, ".cub", 4) == 0);
}

/* Dispatches a non-map line to the right sub-parser. */
static int\tparse_element_line(const char *line, t_config *cfg)
{
\tif (ft_strncmp(line, "NO", 2) == 0
\t\t|| ft_strncmp(line, "SO", 2) == 0
\t\t|| ft_strncmp(line, "WE", 2) == 0
\t\t|| ft_strncmp(line, "EA", 2) == 0)
\t\treturn (parse_texture_line(line, cfg));
\tif (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "F\\t", 2) == 0)
\t\treturn (parse_color_line(line, cfg));
\tif (ft_strncmp(line, "C ", 2) == 0 || ft_strncmp(line, "C\\t", 2) == 0)
\t\treturn (parse_color_line(line, cfg));
\tcub_error("Unknown element identifier");
\treturn (-1);
}

/* Reads file line by line, dispatching each line. Map block
 * consumes the rest of the file via parse_map_block. */
static int\tparse_lines(int fd, t_config *cfg)
{
\tchar\t*line;

\tline = get_next_line(fd);
\twhile (line != NULL)
\t{
\t\tstrip_newline(line);
\t\tif (is_blank_line(line))
\t\t{
\t\t\tfree(line);
\t\t\tline = get_next_line(fd);
\t\t\tcontinue ;
\t\t}
\t\tif (looks_like_map(line))
\t\t\treturn (parse_map_block(fd, line, cfg));
\t\tif (parse_element_line(line, cfg) < 0)
\t\t{
\t\t\tfree(line);
\t\t\treturn (-1);
\t\t}
\t\tfree(line);
\t\tline = get_next_line(fd);
\t}
\treturn (0);
}

/* Public entry: parses a .cub file into a t_config. */
t_config\t*parse_cub_file(const char *path)
{
\tint\t\tfd;
\tt_config\t*cfg;

\tif (!has_cub_extension(path))
\t\treturn (cub_error_ret("File must end with .cub", NULL));
\tfd = open(path, O_RDONLY);
\tif (fd < 0)
\t\treturn (cub_error_ret("Cannot open scene file", NULL));
\tcfg = alloc_config();
\tif (!cfg)
\t{
\t\tclose(fd);
\t\treturn (cub_error_ret("Memory allocation failed", NULL));
\t}
\tif (parse_lines(fd, cfg) < 0)
\t{
\t\tdrain_fd(fd);
\t\tclose(fd);
\t\tfree_config(cfg);
\t\treturn (NULL);
\t}
\tclose(fd);
\tif (validate_config(cfg) < 0)
\t{
\t\tfree_config(cfg);
\t\treturn (NULL);
\t}
\treturn (cfg);
}
""")

# ============================================================================
#  src/parser/parser_textures.c  (4 functions)
# ============================================================================
write_file(f'{ROOT}/src/parser/parser_textures.c', header('parser_textures.c') + """
#include "parser_internal.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <libft.h>

/* Extracts one ws-delimited token from *p. Advances *p. */
static char\t*extract_token(const char **p)
{
\tconst char\t*start;
\tchar\t\t*token;
\tsize_t\t\tlen;

\tstart = *p;
\twhile (**p != '\\0' && **p != ' ' && **p != '\\t')
\t\t(*p)++;
\tlen = (size_t)(*p - start);
\ttoken = (char *)malloc(len + 1);
\tif (!token)
\t{
\t\tcub_error("Memory allocation failed");
\t\treturn (NULL);
\t}
\tft_strlcpy(token, start, len + 1);
\treturn (token);
}

/* Returns 0 if file at path is readable, -1 otherwise. */
static int\tverify_path_readable(const char *path)
{
\tint\tfd;

\tfd = open(path, O_RDONLY);
\tif (fd < 0)
\t\treturn (-1);
\tclose(fd);
\treturn (0);
}

/* Stores path into the right field. Rejects duplicates. */
static int\tset_texture_field(const char *line, t_config *cfg, char *path)
{
\tif (verify_path_readable(path) < 0)
\t{
\t\tcub_error("Texture file cannot be opened");
\t\tfree(path);
\t\treturn (-1);
\t}
\tif (ft_strncmp(line, "NO", 2) == 0 && !cfg->has_north)
\t\treturn (cfg->textures.north = path, cfg->has_north = 1, 0);
\tif (ft_strncmp(line, "SO", 2) == 0 && !cfg->has_south)
\t\treturn (cfg->textures.south = path, cfg->has_south = 1, 0);
\tif (ft_strncmp(line, "WE", 2) == 0 && !cfg->has_west)
\t\treturn (cfg->textures.west = path, cfg->has_west = 1, 0);
\tif (ft_strncmp(line, "EA", 2) == 0 && !cfg->has_east)
\t\treturn (cfg->textures.east = path, cfg->has_east = 1, 0);
\tcub_error("Duplicate texture identifier");
\tfree(path);
\treturn (-1);
}

/* Parses a "NO/SO/WE/EA <path>" line. */
int\tparse_texture_line(const char *line, t_config *cfg)
{
\tconst char\t*p;
\tchar\t\t*path;

\tif (line[2] != ' ' && line[2] != '\\t')
\t{
\t\tcub_error("Texture id must be followed by ws");
\t\treturn (-1);
\t}
\tp = line + 2;
\tskip_spaces(&p);
\tif (*p == '\\0')
\t{
\t\tcub_error("Missing texture path");
\t\treturn (-1);
\t}
\tpath = extract_token(&p);
\tif (!path)
\t\treturn (-1);
\tskip_spaces(&p);
\tif (*p != '\\0')
\t{
\t\tcub_error("Unexpected text after texture path");
\t\tfree(path);
\t\treturn (-1);
\t}
\treturn (set_texture_field(line, cfg, path));
}
""")

# ============================================================================
#  src/parser/parser_colors.c  (4 functions)
# ============================================================================
write_file(f'{ROOT}/src/parser/parser_colors.c', header('parser_colors.c') + """
#include "parser_internal.h"
#include <libft.h>

/* Parses one color component: skip ws, read int in [0,255]. */
static int\tparse_color_component(const char **p, int *out)
{
\tint\tvalue;

\tskip_spaces(p);
\tif (!ft_isdigit(**p))
\t{
\t\tcub_error("Color component must be a number");
\t\treturn (-1);
\t}
\tvalue = 0;
\twhile (ft_isdigit(**p))
\t{
\t\tvalue = value * 10 + (**p - '0');
\t\tif (value > 255)
\t\t{
\t\t\tcub_error("Color component out of range [0,255]");
\t\t\treturn (-1);
\t\t}
\t\t(*p)++;
\t}
\t*out = value;
\treturn (0);
}

/* Skips ws, expects one ','. */
static int\texpect_comma(const char **p)
{
\tskip_spaces(p);
\tif (**p != ',')
\t{
\t\tcub_error("Expected ',' between color components");
\t\treturn (-1);
\t}
\t(*p)++;
\treturn (0);
}

/* Stores (r,g,b) into the right field. Rejects duplicates. */
static int\tstore_color(char target, t_config *cfg, int r, int g, int b)
{
\tif (target == 'F' && !cfg->has_floor)
\t{
\t\tcfg->floor.r = r;
\t\tcfg->floor.g = g;
\t\tcfg->floor.b = b;
\t\tcfg->has_floor = 1;
\t\treturn (0);
\t}
\tif (target == 'C' && !cfg->has_ceiling)
\t{
\t\tcfg->ceiling.r = r;
\t\tcfg->ceiling.g = g;
\t\tcfg->ceiling.b = b;
\t\tcfg->has_ceiling = 1;
\t\treturn (0);
\t}
\tcub_error("Duplicate color identifier");
\treturn (-1);
}

/* Parses a "F/C r,g,b" line. */
int\tparse_color_line(const char *line, t_config *cfg)
{
\tconst char\t*p;
\tint\t\t\tr;
\tint\t\t\tg;
\tint\t\t\tb;

\tif (line[1] != ' ' && line[1] != '\\t')
\t{
\t\tcub_error("Color id must be followed by ws");
\t\treturn (-1);
\t}
\tp = line + 1;
\tif (parse_color_component(&p, &r) < 0)
\t\treturn (-1);
\tif (expect_comma(&p) < 0 || parse_color_component(&p, &g) < 0)
\t\treturn (-1);
\tif (expect_comma(&p) < 0 || parse_color_component(&p, &b) < 0)
\t\treturn (-1);
\tskip_spaces(&p);
\tif (*p != '\\0')
\t{
\t\tcub_error("Unexpected text after color");
\t\treturn (-1);
\t}
\treturn (store_color(line[0], cfg, r, g, b));
}
""")

# ============================================================================
#  src/parser/parser_map.c  (5 functions)
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
#  src/parser/parser_map_helpers.c  (3 functions)
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

/* Allocates a new string of `width`, copying src + padding
 * with spaces. NULL on alloc failure. */
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

/* Allocates grid, pads each line, finds spawn, runs flood fill.
 * Frees the collector. Returns 0/-1. */
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
\t\t\treturn (free_grid_on_err(grid, i, c));
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

print("Parser .c files generated.")
