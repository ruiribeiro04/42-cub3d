/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-maga <vde-maga@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 17:08:34 by vde-maga          #+#    #+#             */
/*   Updated: 2026/07/17 17:08:37 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

# include "cub3d.h"

# define MAP_MAX_CELLS		10000000
# define SPRITE_PATH_MAX	240
# define TAB_WIDTH			4

char		*get_next_line(int fd);

int			ft_is_blank_line(const char *line);
int			ft_looks_like_map(const char *line);
void		ft_skip_spaces(const char **p);
int			ft_is_map_char(char c);
void		ft_strip_newline(char *line);
void		ft_drain_fd(int fd);
char		*ft_expand_tabs(const char *line);

typedef struct s_map_collector
{
	char	**lines;
	int		count;
	int		capacity;
	int		max_width;
}			t_map_collector;

int			ft_collector_init(t_map_collector *c, char *first_line);
int			ft_collector_add(t_map_collector *c, char *line);
void		ft_collector_free(t_map_collector *c);
int			ft_validate_map_line(const char *line);
int			ft_process_map_line(char **line);
char		*ft_pad_line(const char *src, int width);
int			ft_finalize_map(t_config *cfg, t_map_collector *c);

int			ft_parse_texture_line(const char *line, t_config *cfg);
int			ft_parse_color_line(const char *line, t_config *cfg);
int			ft_parse_sprite_line(const char *line, t_config *cfg);
int			ft_parse_door_line(const char *line, t_config *cfg);
int			ft_parse_element_line(const char *line, t_config *cfg);
int			ft_parse_map_block(int fd, char *first_line, t_config *cfg);
int			ft_parse_lines(int fd, t_config *cfg);

char		*ft_extract_path(const char *line);

int			ft_validate_config(t_config *cfg);
int			ft_find_spawn(t_config *cfg);
int			ft_flood_fill_check(t_config *cfg);
void		ft_convert_sprites_to_floor(t_config *cfg);

typedef struct s_flood_ctx
{
	t_config	*cfg;
	char		*visited;
	int			*queue;
	int			q_tail;
}			t_flood_ctx;

#endif
