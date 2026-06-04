/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:18:31 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

int		ft_parse_cub_file(char *filename, t_game *game);
int		ft_open_and_validate(char *filename);
char	*ft_parse_elements(int fd, t_game *game);
int		ft_parse_texture(char *line, t_game *game);
int		ft_parse_color(char *line, t_game *game);
char	**ft_parse_map_grid(int fd, t_game *game, char *first_line);
int		ft_validate_map_chars(t_game *game);
int		ft_validate_map_closed(t_game *game);
int		ft_init_player_from_map(t_game *game);
int		validate_row_boundaries(t_game *game, int y, int x);
int		validate_space_neighbors(t_game *game, int y, int x);
int		validate_overhangs(t_game *game, int y, int x);
int		validate_texture_path(char *path);
int		validate_all_textures(t_game *game);
char	**realloc_map(char **map, int current_size);
void	strip_newline(char *line);
char	*skip_empty_and_read(int fd);
int		add_line_to_map(char *line, char ***map, int *i, t_game *game);
int		ft_extract_sprites(t_game *game);
void	ft_free_parsed_sprites(t_game *game);

void	ft_free_split_arr(char **values);
int		is_valid_number(char *str);
void	ft_replace_commas_with_spaces(char *str);
int		ft_validate_range_and_assign(int *r, int *g, int *b, char **values);
int		ft_check_numeric_values(char **values);
int		ft_is_element_line(char *line);
int		ft_is_map_line(char *line);
int		ft_has_all_required_elements(t_game *game);
char	*ft_skip_empty_lines(int fd);
void	ft_print_missing_elements_error(void);
void	ft_free_parser_paths(t_game *game);
void	ft_free_parser_map(t_game *game);
void	ft_flush_gnl_buffer(int fd);
void	ft_print_invalid_char_error(char c, int y, int x);
int		ft_is_valid_map_char(char c);
int		ft_check_row_chars(char **map, int y);
int		ft_find_player_position(t_game *game, int *py, int *px);
int		ft_flood_fill(char **map_copy, int y, int x);
char	**ft_copy_map(t_game *game);

#endif
