#ifndef GRAPHICS_H
# define GRAPHICS_H

void    ft_put_pixel_to_img(t_game *game, int x, int y, int color);
void    ft_clear_image(t_game *game, int color);
void    ft_draw_filled_square(t_game *game, int x_start, int y_start, int size, int color);
void    ft_draw_map(t_game *game);

#endif