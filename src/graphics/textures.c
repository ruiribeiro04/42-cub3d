/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 15:36:10 by ruiferna          #+#    #+#             */
/*   Updated: 2026/07/17 17:21:00 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include <stdlib.h>


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
