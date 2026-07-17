/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/15 14:45:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"
#include <stdlib.h>

/*
 * Reads the mlx image pixel buffer into a flat int[] cache for fast access
 * during raycasting. Requires 32 bits per pixel (the only bpp the rest of
 * the engine assumes when indexing pixels as int).
 */
static int	cache_pixels(t_texture *tex)
{
	int		x;
	int		y;
	int		num_pixels;
	char	*src;

	if (tex->img.bpp != 32)
		return (ft_cub_error_int("Texture must use 32bpp"));
	num_pixels = tex->img.width * tex->img.height;
	tex->pixels = (int *)malloc(sizeof(int) * num_pixels);
	if (!tex->pixels)
		return (-1);
	src = tex->img.data;
	y = 0;
	while (y < tex->img.height)
	{
		x = 0;
		while (x < tex->img.width)
		{
			tex->pixels[y * tex->img.width + x] = *(int *)(src
					+ y * tex->img.line_len + x * (tex->img.bpp / 8));
			x++;
		}
		y++;
	}
	return (0);
}

/*
 * Loads an XPM file into a t_texture. On any failure the texture is left
 * fully zeroed (ptr == NULL, pixels == NULL) so destroy_texture() can be
 * called again safely without triggering a double-free.
 */
int	ft_load_texture(t_game *game, t_texture *tex, char *path)
{
	tex->pixels = NULL;
	tex->img.ptr = mlx_xpm_file_to_image(game->mlx, path,
			&tex->img.width, &tex->img.height);
	if (!tex->img.ptr)
		return (ft_cub_error_int("Failed to load texture file"));
	tex->img.data = mlx_get_data_addr(tex->img.ptr, &tex->img.bpp,
			&tex->img.line_len, &tex->img.endian);
	if (!tex->img.data)
	{
		ft_destroy_texture(game, tex);
		return (ft_cub_error_int("Failed to get texture data"));
	}
	if (tex->img.width != TEX_SIZE || tex->img.height != TEX_SIZE)
	{
		ft_destroy_texture(game, tex);
		return (ft_cub_error_int("Texture must be 64x64"));
	}
	if (cache_pixels(tex) < 0)
	{
		ft_destroy_texture(game, tex);
		return (ft_cub_error_int("Failed to cache texture pixels"));
	}
	return (0);
}
