#ifndef TEXTURES_H
# define TEXTURES_H

int				ft_load_all_textures(t_game *game);
t_texture		*ft_get_wall_texture(t_game *game);
unsigned int	ft_get_texture_pixel(t_texture *tex, int x, int y);

#endif
