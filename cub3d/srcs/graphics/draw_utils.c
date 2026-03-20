#include "cub3d.h"

/**
 * @file draw_utils.c
 * @brief Image drawing utilities for the renderer.
 *
 * Provides functions to put a pixel into the image buffer and
 * to clear/fill the image with a single color.
 */

/**
 * @brief Write a pixel color into the game's image buffer at (x, y).
 *
 * Safely writes a 32-bit color value into the image buffer stored in
 * `game->data`. If the coordinates are outside the drawable area the
 * function returns without modifying memory.
 *
 * @param game Pointer to the main game structure containing image data.
 * @param x X coordinate of the pixel (0-based).
 * @param y Y coordinate of the pixel (0-based).
 * @param color 32-bit color value to write into the buffer (0xAARRGGBB or 0xRRGGBB).
 */
void	ft_put_pixel_to_img(t_game *game, int x, int y, int color)
{
    char	*dst;

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return ;
    dst = game->data + (y * game->size_line + x * (game->bpp / 8));
    *(unsigned int *)dst = color;
}

/**
 * @brief Fill the entire image buffer with a single color.
 *
 * This function writes the provided color into every pixel of the
 * image buffer associated with `game`. It calculates the total number
 * of pixels from the image stride and the defined `HEIGHT`.
 *
 * @param game Pointer to the main game structure containing image data.
 * @param color 32-bit color value used to clear the image.
 */
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