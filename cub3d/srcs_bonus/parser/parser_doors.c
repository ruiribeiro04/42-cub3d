#include "cub3d.h"

static int	ft_init_doors_map(t_game *game)
{
	int	y;

	if (game->door_count == 0)
	{
		game->doors = NULL;
		game->door_map = NULL;
		return (0);
	}
	game->door_map = malloc(sizeof(t_door **) * game->map_height);
	if (!game->door_map)
		return (1);
	y = 0;
	while (y < game->map_height)
	{
		game->door_map[y] = ft_calloc(game->map_width, sizeof(t_door *));
		if (!game->door_map[y])
			return (1);
		y++;
	}
	game->doors = malloc(sizeof(t_door) * game->door_count);
	if (!game->doors)
		return (1);
	return (0);
}

static void	ft_init_single_door(t_game *game, int i, int x, int y)
{
	game->doors[i].x = x;
	game->doors[i].y = y;
	game->doors[i].state = DOOR_CLOSED;
	game->doors[i].progress = 0.0f;
	game->doors[i].tex.img = NULL;
	game->door_map[y][x] = &game->doors[i];
}

static void	ft_setup_door_data(t_game *game)
{
	int	y;
	int	x;
	int	i;

	i = 0;
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'D')
			{
				ft_init_single_door(game, i, x, y);
				i++;
			}
			x++;
		}
		y++;
	}
}

static int	ft_load_door_textures(t_game *game)
{
	int	i;

	if (ft_load_texture(game, &game->doors[0].tex, "textures/door.xpm"))
		return (1);
	i = 1;
	while (i < game->door_count)
	{
		game->doors[i].tex = game->doors[0].tex;
		i++;
	}
	return (0);
}

int	ft_parse_doors(t_game *game)
{
	int	y;
	int	x;

	game->door_count = 0;
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'D')
				game->door_count++;
			x++;
		}
		y++;
	}
	if (ft_init_doors_map(game))
		return (1);
	ft_setup_door_data(game);
	if (ft_load_door_textures(game))
		return (1);
	return (0);
}
