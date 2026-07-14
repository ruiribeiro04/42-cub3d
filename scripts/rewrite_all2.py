#!/usr/bin/env python3
"""Part 2: parser, raycaster, player, bonus files."""

import os

ROOT = '/home/z/my-project/cub3d'

def h(name):
    login = 'ruiferna'
    mail = 'ruiferna@student.42porto.com'
    created = '2025/07/10 19:00:00'
    updated = '2025/07/11 16:00:00'
    n = name.ljust(51)
    by = f"{login} <{mail}>".ljust(43)
    cr = f"{created} by {login}".ljust(41)
    up = f"{updated} by {login}".ljust(40)
    return (
        "/* ************************************************************************** */\n"
        "/*                                                                            */\n"
        "/*                                                        :::      ::::::::   */\n"
        f"/*   {n}:+:      :+:    :+:   */\n"
        "/*                                                    +:+ +:+         +:+     */\n"
        f"/*   By: {by}+#+  +:+       +#+        */\n"
        "/*                                                +#+#+#+#+#+   +#+           */\n"
        f"/*   Created: {cr}#+#    #+#             */\n"
        f"/*   Updated: {up}###   ########.fr       */\n"
        "/*                                                                            */\n"
        "/* ************************************************************************** */\n"
    )

def w(path, content):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, 'w') as f:
        f.write(content)
    print(f"  wrote {path}")

# =====================================================================
#  src/parser/parser_internal.h
# =====================================================================
w(f'{ROOT}/src/parser/parser_internal.h', h('parser_internal.h') + r"""#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

# include "cub3d.h"

char	*get_next_line(int fd);

int		is_blank_line(const char *line);
int		looks_like_map(const char *line);
void	skip_spaces(const char **p);
int		is_map_char(char c);
void	strip_newline(char *line);
void	drain_fd(int fd);

typedef struct s_map_collector
{
	char	**lines;
	int		count;
	int		capacity;
	int		max_width;
}			t_map_collector;

int		collector_init(t_map_collector *c, char *first_line);
int		collector_add(t_map_collector *c, char *line);
void	collector_free(t_map_collector *c);
int		validate_map_line(const char *line);
char	*pad_line(const char *src, int width);
int		finalize_map(t_config *cfg, t_map_collector *c);

int		parse_texture_line(const char *line, t_config *cfg);
int		parse_color_line(const char *line, t_config *cfg);
int		parse_sprite_line(const char *line, t_config *cfg);
int		parse_door_line(const char *line, t_config *cfg);
int		parse_map_block(int fd, char *first_line, t_config *cfg);

int		validate_config(t_config *cfg);
int		find_spawn(t_config *cfg);
int		flood_fill_check(t_config *cfg);
void	convert_sprites_to_floor(t_config *cfg);

void	free_str_array(char **arr);
t_config	*alloc_config(void);

typedef struct s_flood_ctx
{
	t_config	*cfg;
	char		*visited;
	int			*queue;
	int			q_tail;
}			t_flood_ctx;

#endif
""")

# =====================================================================
#  src/parser/parser_utils.c — MANDATORY (no D/O/2)
# =====================================================================
w(f'{ROOT}/src/parser/parser_utils.c', h('parser_utils.c') + r"""#include "parser_internal.h"
#include <libft.h>

static int	is_space_char(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_blank_line(const char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i] != '\0')
	{
		if (!is_space_char(line[i]))
			return (0);
		i++;
	}
	return (1);
}

void	skip_spaces(const char **p)
{
	if (!p || !*p)
		return ;
	while (is_space_char(**p))
		(*p)++;
}

int	is_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ');
}

int	looks_like_map(const char *line)
{
	int	i;
	int	has_one;

	if (!line)
		return (0);
	i = 0;
	has_one = 0;
	while (line[i] != '\0')
	{
		if (!is_map_char(line[i]))
			return (0);
		if (line[i] == '1')
			has_one = 1;
		i++;
	}
	return (has_one);
}
""")

# =====================================================================
#  src/parser/parser_utils_bonus.c — BONUS (accepts D/O/2)
# =====================================================================
w(f'{ROOT}/src/parser/parser_utils_bonus.c', h('parser_utils_bonus.c') + r"""#include "parser_internal.h"
#include <libft.h>

static int	is_space_char(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_blank_line(const char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i] != '\0')
	{
		if (!is_space_char(line[i]))
			return (0);
		i++;
	}
	return (1);
}

void	skip_spaces(const char **p)
{
	if (!p || !*p)
		return ;
	while (is_space_char(**p))
		(*p)++;
}

int	is_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ' || c == 'D'
		|| c == 'O' || c == '2');
}

int	looks_like_map(const char *line)
{
	int	i;
	int	has_one;

	if (!line)
		return (0);
	i = 0;
	has_one = 0;
	while (line[i] != '\0')
	{
		if (!is_map_char(line[i]))
			return (0);
		if (line[i] == '1')
			has_one = 1;
		i++;
	}
	return (has_one);
}
""")

# =====================================================================
#  src/parser/parser_io.c
# =====================================================================
w(f'{ROOT}/src/parser/parser_io.c', h('parser_io.c') + r"""#include "parser_internal.h"
#include <stdlib.h>
#include <libft.h>

void	strip_newline(char *line)
{
	size_t	len;

	if (!line)
		return ;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[--len] = '\0';
	if (len > 0 && line[len - 1] == '\r')
		line[--len] = '\0';
}

void	drain_fd(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
}
""")

# =====================================================================
#  src/parser/parser.c — dispatches SP and DO
# =====================================================================
w(f'{ROOT}/src/parser/parser.c', h('parser.c') + r"""#include "parser_internal.h"
#include <fcntl.h>
#include <unistd.h>
#include <libft.h>

static int	has_cub_extension(const char *path)
{
	size_t	len;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 5)
		return (0);
	return (ft_strncmp(path + len - 4, ".cub", 4) == 0);
}

static int	parse_element_line(const char *line, t_config *cfg)
{
	if (ft_strncmp(line, "NO", 2) == 0
		|| ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "WE", 2) == 0
		|| ft_strncmp(line, "EA", 2) == 0)
		return (parse_texture_line(line, cfg));
	if (ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "F\t", 2) == 0)
		return (parse_color_line(line, cfg));
	if (ft_strncmp(line, "C ", 2) == 0
		|| ft_strncmp(line, "C\t", 2) == 0)
		return (parse_color_line(line, cfg));
	if (ft_strncmp(line, "SP", 2) == 0)
		return (parse_sprite_line(line, cfg));
	if (ft_strncmp(line, "DO", 2) == 0)
		return (parse_door_line(line, cfg));
	cub_error("Unknown element identifier");
	return (-1);
}

static int	parse_lines(int fd, t_config *cfg)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		strip_newline(line);
		if (is_blank_line(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (looks_like_map(line))
			return (parse_map_block(fd, line, cfg));
		if (parse_element_line(line, cfg) < 0)
		{
			free(line);
			return (-1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

static int	parse_and_validate(int fd, t_config *cfg)
{
	if (parse_lines(fd, cfg) < 0)
	{
		drain_fd(fd);
		return (-1);
	}
	return (validate_config(cfg));
}

t_config	*parse_cub_file(const char *path)
{
	int			fd;
	t_config	*cfg;

	if (!has_cub_extension(path))
		return (cub_error_ret("File must end with .cub", NULL));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (cub_error_ret("Cannot open scene file", NULL));
	cfg = alloc_config();
	if (!cfg)
	{
		close(fd);
		return (cub_error_ret("Memory allocation failed", NULL));
	}
	if (parse_and_validate(fd, cfg) < 0)
	{
		close(fd);
		free_config(cfg);
		return (NULL);
	}
	close(fd);
	return (cfg);
}
""")

# =====================================================================
#  src/parser/parser_textures.c
# =====================================================================
w(f'{ROOT}/src/parser/parser_textures.c', h('parser_textures.c') + r"""#include "parser_internal.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <libft.h>

static char	*extract_token(const char **p)
{
	const char	*start;
	char		*token;
	size_t		len;

	start = *p;
	while (**p != '\0' && **p != ' ' && **p != '\t')
		(*p)++;
	len = (size_t)(*p - start);
	token = (char *)malloc(len + 1);
	if (!token)
	{
		cub_error("Memory allocation failed");
		return (NULL);
	}
	ft_strlcpy(token, start, len + 1);
	return (token);
}

static int	verify_path_readable(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	close(fd);
	return (0);
}

static int	set_texture_field(const char *line, t_config *cfg,
								char *path)
{
	if (verify_path_readable(path) < 0)
	{
		cub_error("Texture file cannot be opened");
		free(path);
		return (-1);
	}
	if (ft_strncmp(line, "NO", 2) == 0 && !cfg->has_north)
		return (cfg->textures.north = path, cfg->has_north = 1, 0);
	if (ft_strncmp(line, "SO", 2) == 0 && !cfg->has_south)
		return (cfg->textures.south = path, cfg->has_south = 1, 0);
	if (ft_strncmp(line, "WE", 2) == 0 && !cfg->has_west)
		return (cfg->textures.west = path, cfg->has_west = 1, 0);
	if (ft_strncmp(line, "EA", 2) == 0 && !cfg->has_east)
		return (cfg->textures.east = path, cfg->has_east = 1, 0);
	cub_error("Duplicate texture identifier");
	free(path);
	return (-1);
}

int	parse_texture_line(const char *line, t_config *cfg)
{
	const char	*p;
	char		*path;

	if (line[2] != ' ' && line[2] != '\t')
		return (cub_error_int("Texture id must be followed by ws"));
	p = line + 2;
	skip_spaces(&p);
	if (*p == '\0')
		return (cub_error_int("Missing texture path"));
	path = extract_token(&p);
	if (!path)
		return (-1);
	skip_spaces(&p);
	if (*p != '\0')
	{
		cub_error("Unexpected text after texture path");
		free(path);
		return (-1);
	}
	return (set_texture_field(line, cfg, path));
}
""")

# =====================================================================
#  src/parser/parser_colors.c
# =====================================================================
w(f'{ROOT}/src/parser/parser_colors.c', h('parser_colors.c') + r"""#include "parser_internal.h"
#include <libft.h>

static int	parse_color_component(const char **p, int *out)
{
	int	value;

	skip_spaces(p);
	if (!ft_isdigit(**p))
		return (cub_error_int("Color component must be a number"));
	value = 0;
	while (ft_isdigit(**p))
	{
		value = value * 10 + (**p - '0');
		if (value > 255)
			return (cub_error_int("Color out of range [0,255]"));
		(*p)++;
	}
	*out = value;
	return (0);
}

static int	expect_comma(const char **p)
{
	skip_spaces(p);
	if (**p != ',')
		return (cub_error_int("Expected ',' between components"));
	(*p)++;
	return (0);
}

static int	store_color(char target, t_config *cfg, t_color *color)
{
	if (target == 'F' && !cfg->has_floor)
	{
		cfg->floor = *color;
		cfg->has_floor = 1;
		return (0);
	}
	if (target == 'C' && !cfg->has_ceiling)
	{
		cfg->ceiling = *color;
		cfg->has_ceiling = 1;
		return (0);
	}
	return (cub_error_int("Duplicate color identifier"));
}

int	parse_color_line(const char *line, t_config *cfg)
{
	const char	*p;
	t_color		color;

	if (line[1] != ' ' && line[1] != '\t')
		return (cub_error_int("Color id must be followed by ws"));
	p = line + 1;
	if (parse_color_component(&p, &color.r) < 0)
		return (-1);
	if (expect_comma(&p) < 0
		|| parse_color_component(&p, &color.g) < 0)
		return (-1);
	if (expect_comma(&p) < 0
		|| parse_color_component(&p, &color.b) < 0)
		return (-1);
	skip_spaces(&p);
	if (*p != '\0')
		return (cub_error_int("Unexpected text after color"));
	return (store_color(line[0], cfg, &color));
}
""")

# =====================================================================
#  src/parser/parser_doors.c — parse DO line
# =====================================================================
w(f'{ROOT}/src/parser/parser_doors.c', h('parser_doors.c') + r"""#include "parser_internal.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <libft.h>

static int	verify_door_path(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	close(fd);
	return (0);
}

int	parse_door_line(const char *line, t_config *cfg)
{
	const char	*p;
	char		*path;
	size_t		len;

	if (cfg->has_door_texture)
		return (cub_error_int("Duplicate DO identifier"));
	if (line[2] != ' ' && line[2] != '\t')
		return (cub_error_int("DO id must be followed by ws"));
	p = line + 2;
	skip_spaces(&p);
	if (*p == '\0')
		return (cub_error_int("Missing door texture path"));
	len = ft_strlen(p);
	while (len > 0 && (p[len - 1] == ' ' || p[len - 1] == '\t'))
		len--;
	path = (char *)malloc(len + 1);
	if (!path)
		return (cub_error_int("Memory allocation failed"));
	ft_strlcpy(path, p, len + 1);
	if (verify_door_path(path) < 0)
	{
		cub_error("Door texture file cannot be opened");
		free(path);
		return (-1);
	}
	cfg->door_texture = path;
	cfg->has_door_texture = 1;
	return (0);
}
""")

# =====================================================================
#  src/parser/parser_sprite.c — base path for multiple frames
# =====================================================================
w(f'{ROOT}/src/parser/parser_sprite.c', h('parser_sprite.c') + r"""#include "parser_internal.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <libft.h>

static char	*extract_sprite_path(const char *line)
{
	const char	*p;
	char		*path;
	size_t		len;

	p = line + 2;
	skip_spaces(&p);
	if (*p == '\0')
	{
		cub_error("Missing sprite texture path");
		return (NULL);
	}
	len = ft_strlen(p);
	while (len > 0 && (p[len - 1] == ' ' || p[len - 1] == '\t'))
		len--;
	path = (char *)malloc(len + 1);
	if (!path)
	{
		cub_error("Memory allocation failed");
		return (NULL);
	}
	ft_strlcpy(path, p, len + 1);
	return (path);
}

int	parse_sprite_line(const char *line, t_config *cfg)
{
	char	*path;

	if (cfg->has_sprite)
		return (cub_error_int("Duplicate SP identifier"));
	if (line[2] != ' ' && line[2] != '\t')
		return (cub_error_int("SP id must be followed by ws"));
	path = extract_sprite_path(line);
	if (!path)
		return (-1);
	cfg->sprite_texture = path;
	cfg->has_sprite = 1;
	return (0);
}
""")

# =====================================================================
#  src/parser/parser_sprite_collect.c
# =====================================================================
w(f'{ROOT}/src/parser/parser_sprite_collect.c', h('parser_sprite_collect.c') + r"""#include "parser_internal.h"
#include <stdlib.h>
#include <libft.h>

static int	count_sprites(t_config *cfg)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (y < cfg->map.height)
	{
		x = 0;
		while (x < cfg->map.width)
		{
			if (cfg->map.grid[y][x] == '2')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static int	alloc_sprite_positions(t_config *cfg)
{
	cfg->sprite_positions = (t_sprite *)malloc(
			sizeof(t_sprite) * cfg->num_sprites);
	if (!cfg->sprite_positions)
	{
		cub_error("Failed to alloc sprite positions");
		cfg->num_sprites = 0;
		return (-1);
	}
	return (0);
}

static void	collect_row(t_config *cfg, int y, int *idx)
{
	int	x;

	x = 0;
	while (x < cfg->map.width)
	{
		if (cfg->map.grid[y][x] == '2')
		{
			cfg->sprite_positions[*idx].x = (double)x + 0.5;
			cfg->sprite_positions[*idx].y = (double)y + 0.5;
			cfg->sprite_positions[*idx].distance = 0.0;
			cfg->map.grid[y][x] = '0';
			(*idx)++;
		}
		x++;
	}
}

void	convert_sprites_to_floor(t_config *cfg)
{
	int	y;
	int	idx;

	cfg->num_sprites = 0;
	cfg->sprite_positions = NULL;
	if (!cfg->has_sprite)
		return ;
	cfg->num_sprites = count_sprites(cfg);
	if (cfg->num_sprites == 0)
		return ;
	if (alloc_sprite_positions(cfg) < 0)
		return ;
	idx = 0;
	y = 0;
	while (y < cfg->map.height)
	{
		collect_row(cfg, y, &idx);
		y++;
	}
}
""")

# =====================================================================
#  src/parser/parser_map.c
# =====================================================================
w(f'{ROOT}/src/parser/parser_map.c', h('parser_map.c') + r"""#include "parser_internal.h"
#include <stdlib.h>
#include <libft.h>

static int	collector_grow(t_map_collector *c)
{
	char	**new_lines;
	int		new_cap;
	int		i;

	new_cap = c->capacity * 2;
	new_lines = (char **)malloc(sizeof(char *) * new_cap);
	if (!new_lines)
		return (cub_error_int("Memory allocation failed"));
	i = 0;
	while (i < c->count)
	{
		new_lines[i] = c->lines[i];
		i++;
	}
	free(c->lines);
	c->lines = new_lines;
	c->capacity = new_cap;
	return (0);
}

int	collector_init(t_map_collector *c, char *first_line)
{
	c->capacity = 16;
	c->lines = (char **)malloc(sizeof(char *) * c->capacity);
	if (!c->lines)
	{
		cub_error("Memory allocation failed");
		free(first_line);
		return (-1);
	}
	c->lines[0] = first_line;
	c->count = 1;
	c->max_width = 0;
	if (first_line)
		c->max_width = (int)ft_strlen(first_line);
	return (0);
}

int	collector_add(t_map_collector *c, char *line)
{
	int	line_len;

	if (c->count >= c->capacity)
	{
		if (collector_grow(c) < 0)
		{
			free(line);
			return (-1);
		}
	}
	c->lines[c->count] = line;
	line_len = (int)ft_strlen(line);
	if (line_len > c->max_width)
		c->max_width = line_len;
	c->count++;
	return (0);
}

void	collector_free(t_map_collector *c)
{
	int	i;

	if (!c->lines)
		return ;
	i = 0;
	while (i < c->count)
	{
		free(c->lines[i]);
		i++;
	}
	free(c->lines);
	c->lines = NULL;
}

int	parse_map_block(int fd, char *first_line, t_config *cfg)
{
	t_map_collector	c;
	char			*line;

	if (collector_init(&c, first_line) < 0)
		return (-1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		strip_newline(line);
		if (validate_map_line(line) < 0)
		{
			free(line);
			collector_free(&c);
			return (-1);
		}
		if (collector_add(&c, line) < 0)
		{
			collector_free(&c);
			return (-1);
		}
		line = get_next_line(fd);
	}
	return (finalize_map(cfg, &c));
}
""")

# =====================================================================
#  src/parser/parser_map_helpers.c
# =====================================================================
w(f'{ROOT}/src/parser/parser_map_helpers.c', h('parser_map_helpers.c') + r"""#include "parser_internal.h"
#include <stdlib.h>
#include <libft.h>

int	validate_map_line(const char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!is_map_char(line[i]))
			return (cub_error_int("Invalid character in map"));
		i++;
	}
	return (0);
}

char	*pad_line(const char *src, int width)
{
	char	*dst;
	int		src_len;
	int		i;

	dst = (char *)malloc(sizeof(char) * (width + 1));
	if (!dst)
		return (NULL);
	src_len = (int)ft_strlen(src);
	i = 0;
	while (i < src_len && i < width)
	{
		dst[i] = src[i];
		i++;
	}
	while (i < width)
	{
		dst[i] = ' ';
		i++;
	}
	dst[width] = '\0';
	return (dst);
}

static void	free_grid_partial(char **grid, int count,
								t_map_collector *c)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
	collector_free(c);
}

static int	build_grid(t_config *cfg, t_map_collector *c)
{
	char	**grid;
	int		i;

	grid = (char **)malloc(sizeof(char *) * (c->count + 1));
	if (!grid)
		return (cub_error_int("Memory allocation failed"));
	i = 0;
	while (i < c->count)
	{
		grid[i] = pad_line(c->lines[i], c->max_width);
		if (!grid[i])
		{
			cub_error("Memory allocation failed");
			free_grid_partial(grid, i, c);
			return (-1);
		}
		i++;
	}
	grid[c->count] = NULL;
	cfg->map.grid = grid;
	cfg->map.height = c->count;
	cfg->map.width = c->max_width;
	return (0);
}

int	finalize_map(t_config *cfg, t_map_collector *c)
{
	if (c->count == 0)
	{
		cub_error("No map found");
		collector_free(c);
		return (-1);
	}
	if (build_grid(cfg, c) < 0)
		return (-1);
	collector_free(c);
	if (find_spawn(cfg) < 0)
		return (-1);
	return (flood_fill_check(cfg));
}
""")

# =====================================================================
#  src/parser/parser_spawn.c
# =====================================================================
w(f'{ROOT}/src/parser/parser_spawn.c', h('parser_spawn.c') + r"""#include "parser_internal.h"

static int	is_spawn_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	set_player_angle(t_player *p)
{
	if (p->direction == 'E')
		p->angle = 0.0;
	else if (p->direction == 'S')
		p->angle = PI / 2.0;
	else if (p->direction == 'W')
		p->angle = PI;
	else if (p->direction == 'N')
		p->angle = 3.0 * PI / 2.0;
}

static int	check_spawn_cell(t_config *cfg, int x, int y,
								int *count)
{
	if (!is_spawn_char(cfg->map.grid[y][x]))
		return (0);
	(*count)++;
	if (*count > 1)
		return (cub_error_int("Multiple player spawns"));
	cfg->player.x = (double)x;
	cfg->player.y = (double)y;
	cfg->player.direction = cfg->map.grid[y][x];
	cfg->map.grid[y][x] = '0';
	return (0);
}

int	find_spawn(t_config *cfg)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (y < cfg->map.height)
	{
		x = 0;
		while (x < cfg->map.width)
		{
			if (check_spawn_cell(cfg, x, y, &count) < 0)
				return (-1);
			x++;
		}
		y++;
	}
	if (count == 0)
		return (cub_error_int("No player spawn found"));
	set_player_angle(&cfg->player);
	cfg->has_player = 1;
	convert_sprites_to_floor(cfg);
	return (0);
}
""")

# =====================================================================
#  src/parser/parser_flood_fill.c
# =====================================================================
w(f'{ROOT}/src/parser/parser_flood_fill.c', h('parser_flood_fill.c') + r"""#include "parser_internal.h"
#include <stdlib.h>
#include <libft.h>

static int	explore(t_flood_ctx *ctx, int x, int y)
{
	int	idx;
	int	cell;

	if (x < 0 || x >= ctx->cfg->map.width)
		return (-1);
	if (y < 0 || y >= ctx->cfg->map.height)
		return (-1);
	idx = y * ctx->cfg->map.width + x;
	if (ctx->visited[idx])
		return (0);
	cell = ctx->cfg->map.grid[y][x];
	if (cell == '1')
		return (0);
	if (cell == ' ')
		return (-1);
	ctx->visited[idx] = 1;
	ctx->queue[ctx->q_tail++] = idx;
	return (0);
}

static int	flood_fill_iter(t_config *cfg, char *visited,
							int sx, int sy)
{
	t_flood_ctx	ctx;
	int			q_head;
	int			idx;
	int			x;
	int			y;

	ctx.cfg = cfg;
	ctx.visited = visited;
	ctx.q_tail = 0;
	ctx.queue = (int *)malloc(sizeof(int)
			* (cfg->map.height * cfg->map.width));
	if (!ctx.queue)
		return (-1);
	q_head = 0;
	idx = sy * cfg->map.width + sx;
	ctx.queue[ctx.q_tail++] = idx;
	visited[idx] = 1;
	while (q_head < ctx.q_tail)
	{
		idx = ctx.queue[q_head++];
		x = idx % cfg->map.width;
		y = idx / cfg->map.width;
		if (explore(&ctx, x + 1, y) < 0
			|| explore(&ctx, x - 1, y) < 0
			|| explore(&ctx, x, y + 1) < 0
			|| explore(&ctx, x, y - 1) < 0)
		{
			free(ctx.queue);
			return (-1);
		}
	}
	free(ctx.queue);
	return (0);
}

int	flood_fill_check(t_config *cfg)
{
	char	*visited;
	int		result;
	int		map_size;

	map_size = cfg->map.height * cfg->map.width;
	visited = (char *)malloc((size_t)map_size);
	if (!visited)
		return (cub_error_int("Memory allocation failed"));
	ft_bzero(visited, (size_t)map_size);
	result = flood_fill_iter(cfg, visited,
			(int)cfg->player.x, (int)cfg->player.y);
	free(visited);
	if (result < 0)
		return (cub_error_int("Map is not closed"));
	return (0);
}
""")

# =====================================================================
#  src/parser/parser_validate.c
# =====================================================================
w(f'{ROOT}/src/parser/parser_validate.c', h('parser_validate.c') + r"""#include "parser_internal.h"

static int	check_missing(int present, const char *name)
{
	if (!present)
		return (cub_error_int(name));
	return (0);
}

int	validate_config(t_config *cfg)
{
	if (check_missing(cfg->has_north, "Missing NO texture") < 0
		|| check_missing(cfg->has_south, "Missing SO texture") < 0
		|| check_missing(cfg->has_west, "Missing WE texture") < 0
		|| check_missing(cfg->has_east, "Missing EA texture") < 0
		|| check_missing(cfg->has_floor, "Missing F color") < 0
		|| check_missing(cfg->has_ceiling, "Missing C color") < 0
		|| check_missing(cfg->has_player, "Missing player spawn") < 0)
		return (-1);
	return (0);
}
""")

# =====================================================================
#  src/utils/free_utils.c
# =====================================================================
w(f'{ROOT}/src/utils/free_utils.c', h('free_utils.c') + r"""#include "cub3d.h"
#include <stdlib.h>
#include <libft.h>

void	free_str_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

t_config	*alloc_config(void)
{
	t_config	*cfg;

	cfg = (t_config *)malloc(sizeof(t_config));
	if (!cfg)
		return (NULL);
	ft_memset(cfg, 0, sizeof(t_config));
	return (cfg);
}

static void	free_texture_paths(t_texture_paths *t)
{
	free(t->north);
	free(t->south);
	free(t->west);
	free(t->east);
}

void	free_config(t_config *config)
{
	if (!config)
		return ;
	free_texture_paths(&config->textures);
	if (config->map.grid)
		free_str_array(config->map.grid);
	free(config->sprite_texture);
	free(config->door_texture);
	free(config->sprite_positions);
	free(config);
}
""")

# =====================================================================
#  src/error/error.c
# =====================================================================
w(f'{ROOT}/src/error/error.c', h('error.c') + r"""#include "cub3d.h"
#include <unistd.h>
#include <libft.h>

static void	putstr_endl(const char *s, int fd)
{
	size_t	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	write(fd, s, len);
	write(fd, "\n", 1);
}

void	cub_error(const char *msg)
{
	putstr_endl("Error", STDERR_FILENO);
	if (msg)
		putstr_endl(msg, STDERR_FILENO);
}

void	*cub_error_ret(const char *msg, void *ret)
{
	cub_error(msg);
	return (ret);
}

int	cub_error_int(const char *msg)
{
	cub_error(msg);
	return (-1);
}
""")

print("=== Part 2 done (parser + utils + error) ===")
