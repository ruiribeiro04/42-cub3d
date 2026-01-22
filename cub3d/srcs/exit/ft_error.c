#include "cub3d.h"

static void	ft_free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static void	ft_free_mlx(t_game *game)
{
	if (game->img && game->mlx)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}


static void	ft_free_textures(t_game *game)
{
	if (game->tex_north.img && game->mlx)
		mlx_destroy_image(game->mlx, game->tex_north.img);
	if (game->tex_south.img && game->mlx)
		mlx_destroy_image(game->mlx, game->tex_south.img);
	if (game->tex_east.img && game->mlx)
		mlx_destroy_image(game->mlx, game->tex_east.img);
	if (game->tex_west.img && game->mlx)
		mlx_destroy_image(game->mlx, game->tex_west.img);
}

static void	ft_free_config_paths(t_game *game)
{
	if (game->path_north)
	{
		free(game->path_north);
		game->path_north = NULL;
	}
	if (game->path_south)
	{
		free(game->path_south);
		game->path_south = NULL;
	}
	if (game->path_east)
	{
		free(game->path_east);
		game->path_east = NULL;
	}
	if (game->path_west)
	{
		free(game->path_west);
		game->path_west = NULL;
	}
}

void	ft_free_game(t_game *game)
{
	if (!game)
		return ;
	ft_free_map(game->map);
	game->map = NULL;
	ft_free_textures(game);
	ft_free_config_paths(game);
	ft_free_mlx(game);
	game->mlx = NULL;
	game->win = NULL;
	game->img = NULL;
}


int	ft_error(t_game *game, char *error_msg)
{
	if (game)
		ft_free_game(game);
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(error_msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (1);
	//exit(EXIT_FAILURE);
}