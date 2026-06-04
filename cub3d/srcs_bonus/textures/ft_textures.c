/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:22:56 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @file ft_textures.c
 * @brief Texture loading and utility helpers.
 *
 * Functions to select wall textures based on raycasting results,
 * load XPM textures into MiniLibX images, read pixels from textures,
 * and free texture resources.
 */

/* TODO(cub3D-#TBD): refactor texture column rendering — see Epic 5 S5.2 */

/**
 * @brief Select the correct wall texture for the current ray.
 *
 * Chooses one of the four wall textures stored in `game` according to
 * the ray side and step direction computed by the raycasting logic.
 *
 * @param game Pointer to the main game structure with ray and texture data.
 * @return Pointer to the `t_texture` corresponding to the wall hit.
 */
t_texture	*ft_get_wall_texture(t_game *game)
{
	if (game->ray.side == 0)
	{
		if (game->ray.step_x < 0)
			return (&game->tex_east);
		else
			return (&game->tex_west);
	}
	else
	{
		if (game->ray.step_y < 0)
			return (&game->tex_south);
		else
			return (&game->tex_north);
	}
}

/**
 * @brief Load a single XPM texture into a `t_texture` structure.
 *
 * Wraps MiniLibX calls to load an XPM file and obtain the raw image
 * data pointer and metadata. The function sets `tex->img`, `tex->data`,
 * `tex->width`, `tex->height`, `tex->bpp`, `tex->size_line`, and `tex->endian`.
 *
 * @param game Pointer to the main game structure containing the `mlx` handle.
 * @param tex Pointer to the texture structure to populate.
 * @param path Filesystem path to the XPM texture file.
 * @return 0 on success, non-zero on failure.
 */
int	ft_load_texture(t_game *game, t_texture *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(game->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
		return (1);
	tex->data = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->size_line, &tex->endian);
	if (!tex->data)
		return (1);
	return (0);
}

/**
 * @brief Load all wall textures defined in the game paths.
 *
 * Attempts to load north, south, east and west textures using the
 * configured paths in the `game` structure. Returns non-zero on any
 * failure to allow the caller to handle resource errors.
 *
 * @param game Pointer to the main game structure with texture paths.
 * @return 0 on success, 1 on any texture load failure.
 */
int	ft_load_all_textures(t_game *game)
{
	if (ft_load_texture(game, &game->tex_north, game->path_north))
		return (1);
	if (ft_load_texture(game, &game->tex_south, game->path_south))
		return (1);
	if (ft_load_texture(game, &game->tex_east, game->path_east))
		return (1);
	if (ft_load_texture(game, &game->tex_west, game->path_west))
		return (1);
	return (0);
}

/**
 * @brief Read a pixel color from a texture image.
 *
 * Returns the 32-bit color value at the given coordinates inside the
 * texture. If the coordinates are out of bounds the function returns 0.
 *
 * @param tex Pointer to the texture to sample.
 * @param x X coordinate inside the texture (0-based).
 * @param y Y coordinate inside the texture (0-based).
 * @return 32-bit color value at (x, y) or 0 if out of bounds.
 */
unsigned int	ft_get_texture_pixel(t_texture *tex, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	pixel = tex->data + (y * tex->size_line + x * (tex->bpp / 8));
	return (*(unsigned int *)pixel);
}

/**
 * @brief Free MiniLibX image resources for all loaded textures.
 *
 * Destroys any MiniLibX image handles associated with the game's
 * textures. The function checks each texture's `img` field before
 * calling `mlx_destroy_image` so it is safe to call even if some
 * textures were not loaded.
 *
 * @param game Pointer to the main game structure containing textures.
 */
void	ft_free_textures(t_game *game)
{
	if (game->tex_north.img)
		mlx_destroy_image(game->mlx, game->tex_north.img);
	if (game->tex_south.img)
		mlx_destroy_image(game->mlx, game->tex_south.img);
	if (game->tex_east.img)
		mlx_destroy_image(game->mlx, game->tex_east.img);
	if (game->tex_west.img)
		mlx_destroy_image(game->mlx, game->tex_west.img);
}
