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

void	ft_free_game(t_game *game)
{
	if (!game)
		return ;
	ft_free_map(game->map);
	ft_free_mlx(game);
}

int	ft_error(t_game *game, char *error_msg)
{
	if (game)
		ft_free_game(game);
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(error_msg, STDERR_FILENO);
	// return (1);
	exit(EXIT_FAILURE);
}