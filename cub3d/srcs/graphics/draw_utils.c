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
void	ft_draw_filled_square(t_game *game, int x_start, int y_start, int size, int color)
{
    int	x;
    int	y;

    y = 0;
    while (y < size)
    {
        x = 0;
        while (x < size)
        {
            ft_put_pixel_to_img(game, x_start + x, y_start + y, color);
            x++;
        }
        y++;
    }
}
void	ft_draw_map(t_game *game)
{
    int	x;
    int	y;
    int	wall_color;
    wall_color = 0x00FF0000;

    y = 0;
    while (game->map[y])
    {
        x = 0;
        while (game->map[y][x])
        {
            if (game->map[y][x] == '1')
                ft_draw_filled_square(game, x * BLOCK, y * BLOCK, BLOCK, wall_color);
            x++;
        }
        y++;
    }
}