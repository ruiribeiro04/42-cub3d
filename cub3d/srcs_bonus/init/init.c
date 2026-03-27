#include "cub3d.h"

static void	ft_init_player_keys(t_player *player)
{
	player->key_up = false;
	player->key_down = false;
	player->key_right = false;
	player->key_left = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

static int	ft_load_all_sprite_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->sprite_count)
	{
		if (ft_load_animation(game, &game->sprites[i], "textures/sprite_", 4))
			return (1);
		i++;
	}
	return (0);
}

static int	ft_init_sprites(t_game *game)
{
	game->z_buffer = malloc(sizeof(double) * WIDTH);
	if (!game->z_buffer)
		return (1);
	if (game->sprite_count > 0)
	{
		if (ft_load_all_sprite_textures(game))
			return (1);
	}
	gettimeofday(&game->last_time, NULL);
	return (0);
}

static int	ft_init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (1);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	if (!game->win)
		return (1);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		return (1);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
	if (!game->data)
		return (1);
	return (0);
}

int	ft_init_game(t_game *game, char *map_file)
{
	ft_memset(game, 0, sizeof(t_game));
	ft_init_player_keys(&game->player);
	if (ft_parse_cub_file(map_file, game))
		return (1);
	if (ft_init_mlx(game))
		return (1);
	game->tex_north.img = NULL;
	game->tex_south.img = NULL;
	game->tex_east.img = NULL;
	game->tex_west.img = NULL;
	if (ft_load_all_textures(game))
		return (1);
	if (ft_init_sprites(game))
		return (1);
	return (0);
}
