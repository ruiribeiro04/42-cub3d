#ifndef GRAPHICS_H
# define GRAPHICS_H

void	ft_put_pixel_to_img(t_game *game, int x, int y, int color);
void	ft_clear_image(t_game *game, int color);
void	ft_draw_rect(t_game *game, t_point pos, int size, int color);

#endif
