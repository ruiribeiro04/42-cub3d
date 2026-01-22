#include "cub3d.h"

int	ft_parse_cub_file(char *filename, t_game *game)
{
	int		fd;
	char	*first_line;

	fd = ft_open_and_validate(filename);
	if (fd < 0)
		return (1);
	first_line = ft_parse_elements(fd, game);
	if (!first_line)
	{
		close(fd);
		return (1);
	}
	game->map = ft_parse_map_grid(fd, game, first_line);
	if (!game->map)
	{
		close(fd);
		ft_free_config(game);
		return (1);
	}
	close(fd);
	if (ft_validate_map_chars(game))
	{
		ft_free_config(game);
		game->map = NULL;
		return (1);
	}
	if (ft_validate_map_closed(game))
	{
		ft_free_config(game);
		game->map = NULL;
		return (1);
	}
	ft_init_player_from_map(game);
	return (0);
}

int	ft_open_and_validate(char *filename)
{
	int	len;
	int	fd;

	len = 0;
	while (filename[len])
		len++;
	if (len < 4 || ft_strncmp(&filename[len - 4], ".cub", 4))
	{
		ft_putstr_fd("Error: Invalid file extension. Must be .cub\n", 2);
		return (-1);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error: Cannot open file ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd("\n", 2);
	}
	return (fd);
}

void	ft_free_config(t_game *game)
{
	int	i;

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
	if (game->map)
	{
		i = 0;
		while (game->map[i])
		{
			free(game->map[i]);
			i++;
		}
		free(game->map);
		game->map = NULL;
	}
}
