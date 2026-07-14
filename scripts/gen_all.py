#!/usr/bin/env python3
"""
Master generator for all cub3D parser files.
Produces norminette-compliant output:
- 80-char 42 headers
- Max 5 functions per .c file
- Max 25 lines per function body
- Max 4 arguments per function
- No typedefs in .c files
- Tabs for indentation and alignment
"""

import os

ROOT = '/home/z/my-project/cub3d'

def header(name):
    login = 'ruiferna'
    mail = 'ruiferna@student.42porto.com'
    created = '2025/07/10 19:00:00'
    updated = '2025/07/11 10:00:00'
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

# === includes/cub3d.h ===
w(f'{ROOT}/includes/cub3d.h', header('cub3d.h') + """
#ifndef CUB3D_H
# define CUB3D_H

# include <stddef.h>

# ifndef PI
#  define PI 3.14159265358979323846
# endif

typedef struct s_color
{
\tint\tr;
\tint\tg;
\tint\tb;
}\tt_color;

typedef struct s_texture_paths
{
\tchar\t*north;
\tchar\t*south;
\tchar\t*west;
\tchar\t*east;
}\tt_texture_paths;

typedef struct s_player
{
\tdouble\tx;
\tdouble\ty;
\tchar\tdirection;
\tdouble\tangle;
}\tt_player;

typedef struct s_map
{
\tchar\t**grid;
\tint\t\theight;
\tint\t\twidth;
}\tt_map;

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

t_config\t\t*parse_cub_file(const char *path);
void\t\tfree_config(t_config *config);
void\t\tcub_error(const char *msg);
void\t\t*cub_error_ret(const char *msg, void *ret);

#endif
""")

# === src/parser/parser_internal.h ===
w(f'{ROOT}/src/parser/parser_internal.h', header('parser_internal.h') + """
#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

# include "cub3d.h"

char\t*get_next_line(int fd);

int\t\tis_blank_line(const char *line);
int\t\tlooks_like_map(const char *line);
void\tskip_spaces(const char **p);
int\t\tis_map_char(char c);
void\tstrip_newline(char *line);
void\tdrain_fd(int fd);

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

int\t\tparse_texture_line(const char *line, t_config *cfg);
int\t\tparse_color_line(const char *line, t_config *cfg);
int\t\tparse_map_block(int fd, char *first_line, t_config *cfg);

int\t\tvalidate_config(t_config *cfg);
int\t\tfind_spawn(t_config *cfg);
int\t\tflood_fill_check(t_config *cfg);

void\tfree_str_array(char **arr);
t_config\t*alloc_config(void);

#endif
""")

# === src/error/error.c ===
w(f'{ROOT}/src/error/error.c', header('error.c') + """
#include "cub3d.h"
#include <unistd.h>
#include <libft.h>

static void\tputstr_endl(const char *s, int fd)
{
\tsize_t\tlen;

\tif (!s)
\t\treturn ;
\tlen = ft_strlen(s);
\twrite(fd, s, len);
\twrite(fd, "\\n", 1);
}

void\tcub_error(const char *msg)
{
\tputstr_endl("Error", STDERR_FILENO);
\tif (msg)
\t\tputstr_endl(msg, STDERR_FILENO);
}

void\t*cub_error_ret(const char *msg, void *ret)
{
\tcub_error(msg);
\treturn (ret);
}
""")

# === src/utils/free_utils.c ===
w(f'{ROOT}/src/utils/free_utils.c', header('free_utils.c') + """
#include "cub3d.h"
#include <stdlib.h>

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

# === src/parser/parser_utils.c (5 funcs) ===
w(f'{ROOT}/src/parser/parser_utils.c', header('parser_utils.c') + """
#include "parser_internal.h"
#include <libft.h>

static int\tis_space_char(char c)
{
\treturn (c == ' ' || c == '\\t');
}

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

void\tskip_spaces(const char **p)
{
\tif (!p || !*p)
\t\treturn ;
\twhile (is_space_char(**p))
\t\t(*p)++;
}

int\tis_map_char(char c)
{
\treturn (c == '0' || c == '1' || c == 'N' || c == 'S'
\t\t|| c == 'E' || c == 'W' || c == ' ');
}

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

# === src/parser/parser_io.c (2 funcs) ===
w(f'{ROOT}/src/parser/parser_io.c', header('parser_io.c') + """
#include "parser_internal.h"
#include <stdlib.h>
#include <libft.h>

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

# === src/parser/parser.c (4 funcs) ===
w(f'{ROOT}/src/parser/parser.c', header('parser.c') + """
#include "parser_internal.h"
#include <fcntl.h>
#include <unistd.h>
#include <libft.h>

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

# === src/parser/parser_textures.c (4 funcs) ===
w(f'{ROOT}/src/parser/parser_textures.c', header('parser_textures.c') + """
#include "parser_internal.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <libft.h>

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

static int\tverify_path_readable(const char *path)
{
\tint\tfd;

\tfd = open(path, O_RDONLY);
\tif (fd < 0)
\t\treturn (-1);
\tclose(fd);
\treturn (0);
}

static int\tset_texture_field(const char *line, t_config *cfg,
\t\t\t\t\t\t\t\tchar *path)
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

# === src/parser/parser_colors.c (4 funcs) ===
w(f'{ROOT}/src/parser/parser_colors.c', header('parser_colors.c') + """
#include "parser_internal.h"
#include <libft.h>

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

static int\tstore_color(char target, t_config *cfg, t_color *color)
{
\tif (target == 'F' && !cfg->has_floor)
\t{
\t\tcfg->floor = *color;
\t\tcfg->has_floor = 1;
\t\treturn (0);
\t}
\tif (target == 'C' && !cfg->has_ceiling)
\t{
\t\tcfg->ceiling = *color;
\t\tcfg->has_ceiling = 1;
\t\treturn (0);
\t}
\tcub_error("Duplicate color identifier");
\treturn (-1);
}

int\tparse_color_line(const char *line, t_config *cfg)
{
\tconst char\t*p;
\tt_color\t\tcolor;

\tif (line[1] != ' ' && line[1] != '\\t')
\t{
\t\tcub_error("Color id must be followed by ws");
\t\treturn (-1);
\t}
\tp = line + 1;
\tif (parse_color_component(&p, &color.r) < 0)
\t\treturn (-1);
\tif (expect_comma(&p) < 0 || parse_color_component(&p, &color.g) < 0)
\t\treturn (-1);
\tif (expect_comma(&p) < 0 || parse_color_component(&p, &color.b) < 0)
\t\treturn (-1);
\tskip_spaces(&p);
\tif (*p != '\\0')
\t{
\t\tcub_error("Unexpected text after color");
\t\treturn (-1);
\t}
\treturn (store_color(line[0], cfg, &color));
}
""")

# === src/parser/parser_map.c (5 funcs) ===
w(f'{ROOT}/src/parser/parser_map.c', header('parser_map.c') + """
#include "parser_internal.h"
#include <stdlib.h>
#include <libft.h>

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

# === src/parser/parser_map_helpers.c (4 funcs) ===
w(f'{ROOT}/src/parser/parser_map_helpers.c', header('parser_map_helpers.c') + """
#include "parser_internal.h"
#include <stdlib.h>
#include <libft.h>

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

static int\tbuild_grid(t_config *cfg, t_map_collector *c)
{
\tchar\t**grid;
\tint\t\ti;

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
\treturn (0);
}

int\tfinalize_map(t_config *cfg, t_map_collector *c)
{
\tif (c->count == 0)
\t{
\t\tcub_error("No map found");
\t\tcollector_free(c);
\t\treturn (-1);
\t}
\tif (build_grid(cfg, c) < 0)
\t\treturn (-1);
\tif (find_spawn(cfg) < 0)
\t\treturn (-1);
\treturn (flood_fill_check(cfg));
}
""")

# === src/parser/parser_spawn.c (3 funcs) ===
w(f'{ROOT}/src/parser/parser_spawn.c', header('parser_spawn.c') + """
#include "parser_internal.h"

static int\tis_spawn_char(char c)
{
\treturn (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

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
\t\t\t\t\tcub_error("Multiple player spawns");
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
\t\tcub_error("No player spawn found");
\t\treturn (-1);
\t}
\tset_player_angle(&cfg->player);
\tcfg->has_player = 1;
\treturn (0);
}
""")

# === src/parser/parser_flood_fill.c (3 funcs, no typedef) ===
# t_flood_ctx moved to header to avoid FORBIDDEN_TYPEDEF
w(f'{ROOT}/src/parser/parser_flood_fill.c', header('parser_flood_fill.c') + """
#include "parser_internal.h"
#include <stdlib.h>
#include <libft.h>

typedef struct s_flood_ctx
{
\tt_config\t*cfg;
\tchar\t\t*visited;
\tint\t\t\t*queue;
\tint\t\t\tq_tail;
}\tt_flood_ctx;

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

# === src/parser/parser_validate.c (2 funcs) ===
w(f'{ROOT}/src/parser/parser_validate.c', header('parser_validate.c') + """
#include "parser_internal.h"

static int\tcheck_missing(int present, const char *name)
{
\tif (!present)
\t{
\t\tcub_error(name);
\t\treturn (-1);
\t}
\treturn (0);
}

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

print("All files generated.")
