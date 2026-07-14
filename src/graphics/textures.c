/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/07/11 16:00:00 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"
#include <stdlib.h>

static int	cache_pixels(t_texture *tex)
{
	int		i;
	int		num_pixels;
	char	*src;

	num_pixels = tex->img.width * tex->img.height;
	tex->pixels = (int *)malloc(sizeof(int) * num_pixels);
	if (!tex->pixels)
		return (-1);
	src = tex->img.data;
	i = 0;
	while (i < num_pixels)
	{
		tex->pixels[i] = *(int *)(src + i * (tex->img.bpp / 8));
		i++;
	}
	return (0);
}

int	load_texture(t_game *game, t_texture *tex, char *path)
{
	tex->img.ptr = mlx_xpm_file_to_image(game->mlx, path,
			&tex->img.width, &tex->img.height);
	if (!tex->img.ptr)
		return (cub_error_int("Failed to load texture file"));
	tex->img.data = mlx_get_data_addr(tex->img.ptr, &tex->img.bpp,
			&tex->img.line_len, &tex->img.endian);
	if (!tex->img.data)
	{
		mlx_destroy_image(game->mlx, tex->img.ptr);
		return (cub_error_int("Failed to get texture data"));
	}
	if (cache_pixels(tex) < 0)
	{
		mlx_destroy_image(game->mlx, tex->img.ptr);
		return (cub_error_int("Failed to cache texture pixels"));
	}
	return (0);
}
