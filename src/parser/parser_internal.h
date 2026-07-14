/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/11 16:00:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

# include "cub3d.h"

char		*get_next_line(int fd);

int			is_blank_line(const char *line);
int			looks_like_map(const char *line);
void		skip_spaces(const char **p);
int			is_map_char(char c);
void		strip_newline(char *line);
void		drain_fd(int fd);

typedef struct s_map_collector
{
	char	**lines;
	int		count;
	int		capacity;
	int		max_width;
}			t_map_collector;

int			collector_init(t_map_collector *c, char *first_line);
int			collector_add(t_map_collector *c, char *line);
void		collector_free(t_map_collector *c);
int			validate_map_line(const char *line);
char		*pad_line(const char *src, int width);
int			finalize_map(t_config *cfg, t_map_collector *c);

int			parse_texture_line(const char *line, t_config *cfg);
int			parse_color_line(const char *line, t_config *cfg);
int			parse_sprite_line(const char *line, t_config *cfg);
int			parse_door_line(const char *line, t_config *cfg);
int			parse_map_block(int fd, char *first_line, t_config *cfg);

int			validate_config(t_config *cfg);
int			find_spawn(t_config *cfg);
int			flood_fill_check(t_config *cfg);
void		convert_sprites_to_floor(t_config *cfg);

void		free_str_array(char **arr);

t_config	*alloc_config(void);

typedef struct s_flood_ctx
{
	t_config	*cfg;
	char		*visited;
	int			*queue;
	int			q_tail;
}			t_flood_ctx;

#endif
