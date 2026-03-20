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
void	ft_init_player_from_map(t_game *game);
int		validate_row_boundaries(t_game *game, int y, int x);
int		validate_space_neighbors(t_game *game, int y, int x);
int		validate_overhangs(t_game *game, int y, int x);
char	**realloc_map(char **map, int current_size);
void	strip_newline(char *line);
char	*skip_empty_and_read(int fd);
int		add_line_to_map(char *line, char ***map, int *i, t_game *game);

#endif
