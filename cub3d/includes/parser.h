#ifndef PARSER_H
# define PARSER_H

int		ft_parse_cub_file(char *filename, t_game *game);
int		ft_open_and_validate(char *filename);
int		ft_parse_elements(int fd, t_game *game);
int		ft_parse_texture(char *line, t_game *game);
int		ft_parse_color(char *line, t_game *game);
char	**ft_parse_map_grid(int fd, t_game *game);
int		ft_validate_map_chars(t_game *game);
int		ft_validate_map_closed(t_game *game);
void	ft_init_player_from_map(t_game *game);
void	ft_free_config(t_game *game);
char	*get_first_map_line(void);

#endif
