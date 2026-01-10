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

static void	ft_init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->angle = PI / 2;
	ft_init_player_keys(player);
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
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->size_line, &game->endian);
	if (!game->data)
		return (1);
	return (0);
}

int	ft_init_game(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	ft_init_player(&game->player);
	game->map = ft_get_map();
	if (!game->map)
		return (1);
	if (ft_init_mlx(game))
		return (1);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}