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
int		validate_texture_path(char *path);
int		validate_all_textures(t_game *game);
char	**realloc_map(char **map, int current_size);
void	strip_newline(char *line);
char	*skip_empty_and_read(int fd);
int		add_line_to_map(char *line, char ***map, int *i, t_game *game);
int		ft_extract_sprites(t_game *game);
void	ft_free_parsed_sprites(t_game *game);

#endif
