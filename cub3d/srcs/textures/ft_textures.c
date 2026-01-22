#include "cub3d.h"

// TODO: Talvez a logica de display das texturas, esteja errada!
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

static int	ft_load_texture(t_game *game, t_texture *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(game->mlx, path, &tex->width, &tex->height);
	if (!tex->img)
		return (1);
	tex->data = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->size_line, &tex->endian);
	if (!tex->data)
		return (1);
	return (0);
}

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

unsigned int	ft_get_texture_pixel(t_texture *tex, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	pixel = tex->data + (y * tex->size_line + x * (tex->bpp / 8));
	return (*(unsigned int *)pixel);
}

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