#include "cub3d.h"

void	ft_put_pixel_to_img(t_game *game, int x, int y, int color)
{
    char	*dst;

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return ;
    dst = game->data + (y * game->size_line + x * (game->bpp / 8));
    *(unsigned int *)dst = color;
}

void	ft_clear_image(t_game *game, int color)
{
    unsigned int *img_buffer_int;
    int           total_pixels;
    int           i;

    img_buffer_int = (unsigned int *)game->data;
    total_pixels = (game->size_line / (game->bpp / 8)) * HEIGHT;
    i = 0;
    while (i < total_pixels)
    {
        img_buffer_int[i] = color;
        i++;
    }
}